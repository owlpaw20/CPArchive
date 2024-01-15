/* 显然，一段区间 [l, r] 最多要画 r - l + 1 笔
 * 而判断某些涂画次数可以被省略的依据：c[x] == c[y] < min{c[i] 其中 x < i < y}
 * 也就是两端颜色相同且中间颜色全部都比两端更深时，
 * 就可以把 x 和 y 上原本涂的两笔减小成一笔 [x, y]
 * 所以如果区间 [l, r] 内满足上式的区间有 x 个，最终需要涂的笔画数就为 r - l + 1 - x
 *
 * 通过维护单调栈（单增）来找到所有符合上式的区间。
 * 如果新插入的元素与栈顶元素相等，则找到了个符合条件的区间，更新 cnt 与栈顶。
 * 通过离线处理所有询问，利用树状数组来维护一段前缀的 x 值，得出答案。*/

#include <stack>
#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 2e5 + 10;

int n, q;
int c[N], ans[N];
vector<PII> qry[N];
stack<int> stk;

struct BinIdxTree {
    int tr[N];

    void inc(int x, int t = 1) {
        for (int i = x; i <= n; i += (i & -i))
            tr[i] += t;
    }

    int diff(int x) {
        int ret = 0;
        for (int i = x; i; i -= (i & -i))
            ret += tr[i];
        return ret;
    }

    int query(int l, int r) { return diff(r) - diff(l - 1); }
} BIT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> c[i];

    // 离线处理所有询问
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        qry[r].emplace_back(l, i);
    }

    // 枚举右端点
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && c[stk.top()] > c[i])  // 维护单调性
            stk.pop();

        if (!stk.empty() && c[stk.top()] == c[i])  // 如果两个元素颜色相等
            BIT.inc(stk.top()), stk.pop();         // 则在树状数组的对应下标的位置更新一次 x
        stk.push(i);                               // 将其加入队列

        for (auto [l, j] : qry[i])                 // 对于右端点为 i 的所有询问，令其左端点为 l
            ans[j] = i - l + 1 - BIT.query(l, i);  // 按照公式计算需要涂画的次数
    }

    // 输出离线处理之后的结果
    for (int i = 1; i <= q; i++)
        cout << ans[i] << endl;
    fflush(stdout);
    return 0;
}
