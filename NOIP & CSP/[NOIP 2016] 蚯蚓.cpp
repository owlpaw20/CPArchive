#include <queue>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using i64 = long long;
using PII = pair<int, int>;

const int N = 1e5 + 5;
const int I32MIN = -(1LL << 31);

int n, m, q, u, v, t;
int x[N];
queue<int> que[3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q >> u >> v >> t;
    for (int i = 1; i <= n; i++) cin >> x[i];

    sort(x + 1, x + n + 1, greater<int>());
    for (int i = 1; i <= n; i++) que[0].push(x[i]);

    for (int i = 0; i < m; i++) {
        auto [num, p] = max({PII(que[0].empty() ? I32MIN : que[0].front(), 0),
                    PII(que[1].empty() ? I32MIN : que[1].front(), 1),
                    PII(que[2].empty() ? I32MIN : que[2].front(), 2)});

        que[p].pop();

        int len = num + q * i;
        int sub1 = (i64)u * len / v;
        int sub2 = len - sub1;

        que[1].push(sub1 - q - q * i);
        que[2].push(sub2 - q - q * i);

        if (i % t == t - 1)
            cout << len << ' ';
    }

    cout << endl;

    for (int i = 1; i <= n + m; i++) {
        auto [num, p] = max({PII(que[0].empty() ? I32MIN : que[0].front(), 0),
                    PII(que[1].empty() ? I32MIN : que[1].front(), 1),
                    PII(que[2].empty() ? I32MIN : que[2].front(), 2)});

        que[p].pop();

        if (i % t == 0)
            cout << num + q* m << ' ';
    }

    cout << endl;
    return fflush(stdout), 0;
}
