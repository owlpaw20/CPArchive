#include <queue>
#include <cstring>
#include <iostream>
#include <unordered_set>
using namespace std;
using lng = long long;

const int N = 1e6 + 10;

int n, m;
queue<int> q;
lng a[N], b[N], sum[N];

bool check(lng x) {
    queue<int> q;
    lng temp = 0;
    fill(sum + 1, sum + n + 1, 0);

    // 遍历带薪员工右边的快乐值情况
    for (int i = 1; i <= n; i++) {
        temp -= q.size();                      // 当前员工的快乐值依赖于前一个员工的快乐值
        if (!q.empty() && i - q.front() >= x)  // 如果有员工超出加快乐值的范围
            q.pop();                           // 移除超出范围的带薪员工
        if (b[i])                              // 如果当前员工带薪
            temp += x, q.push(i);              // 则记录快乐值的一个源头
        sum[i] += temp;                        // 记录快乐值
    }

    while (!q.empty()) q.pop();
    temp = 0;

    // 遍历带薪员工左边的快乐值情况
    for (int i = n; i > 0; i--) {
        temp -= q.size();
        if (!q.empty() && q.front() - i >= x) q.pop();
        if (b[i]) temp += x, sum[i] -= x, q.push(i);
        sum[i] += temp;
    }

    for (int i = 1; i <= n; i++)
        if (sum[i] < a[i])
            return false;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> t, b[t] = true;

    lng l = 1, r = 1e10;
    while (l < r) {
        lng mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << r << endl;
    return 0;
}
