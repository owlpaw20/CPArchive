#pragma GCC optimize("O2")

#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1 << 12;

int n, m;
i64 f[2][N];
bool state[N];

void solve(const int& n, const int& m) {
    memset(f, 0, sizeof f);  // !!!
    for (int i = 0; i < (1 << m); i++) {
        int zero_cnt = 0;
        bool is_even = true;
        for (int j = 0; j < m; j++) {
            if ((i >> j) & 1) {
                if (zero_cnt & 1) {
                    is_even = false;
                    break;
                }
                zero_cnt = 0;
            } else
                zero_cnt += 1;
        }
        if (zero_cnt & 1) is_even = false;
        state[i] = is_even;
    }

    int cur = 0, pre = 1;
    f[pre][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            f[cur][j] = 0;
            for (int k = 0; k < (1 << m); k++)
                if (!(j & k) and state[j | k])
                    f[cur][j] += f[pre][k];
        }
        swap(cur, pre);
    }

    cout << f[pre][0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m && n) solve(n, m);

    fflush(stdout);
    return 0;
}
