#include <vector>
#include <numeric>
#include <iostream>
#define endl '\n'
using namespace std;

struct DisjointSet {
    vector<int> p;
    vector<int> cnt;

    void init(int n) {
        p.resize(n + 5);
        cnt.assign(n + 5, 1);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        return p[x] = y, cnt[y] += cnt[x], true;
    }
    int size_of(int x) {
        return cnt[find(x)];
    }
};

const int INFP = 0x3F3F3F3F;
const int INFN = 0xCFCFCFCF;

int C, T;
DisjointSet DSU;
vector<int> val; // 各个变量的初始值

void solve() {
    int n, m;
    cin >> n >> m;
    DSU.init(n * 2);
    val.resize(n + 5);
    iota(val.begin(), val.end(), 0); // 初始化各变量的初始值

    char type;
    int x, y;
    while (m--) {
        cin >> type;
        if (type == '+') {
            cin >> x >> y; // 直接赋值操作
            val[x] = val[y]; // 相当于传递了真假性
        } else if (type == '-') {
            cin >> x >> y; // 取非再赋值操作
            val[x] = -val[y]; // 相当于反转了真假性
        } else {
            cin >> x;
            if (type == 'U') val[x] = 0; // 0 不论正负均为 0，故表示未知
            else if (type == 'T') val[x] = INFP; // 不处理逻辑常量为真的情况
            else if (type == 'F') val[x] = INFN; // 不处理逻辑常量为假的情况
        }
    }

    for (int i = 1; i <= n; i++) {
        // 不处理最终被赋值为常量的变量
        if (abs(val[i]) < 1) continue;
        if (abs(val[i]) > n) continue;

        // 1 ~ N 表示真值，N+1 ~ 2N 表示假值
        // 合并操作表示这两个值之间具有相等关系
        if (val[i] > 0) { // 如果该变量最终的真假性与初始值相同
            DSU.merge(i, val[i]); // 合并当前变量的真值和初始值的真值
            DSU.merge(i + n, val[i] + n); // 合并当前变量的假值和初始值的假值
        } else { // 如果该变量最终的真假性与初始值不同
            DSU.merge(i, -val[i] + n); // 合并当前变量的真值和初始值的假值
            DSU.merge(i + n, -val[i]); // 合并当前变量的假值和初始值的真值
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (val[i] == 0) // 如果有未知变量
            ans += DSU.size_of(i); // 则最终与其相关的所有变量均一定为未知
        if (DSU.find(i) == DSU.find(i + n)) // 如果当前变量的真值与假值相同
            ans += 1; // 说明该值一定为未知
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> C >> T;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
