#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 15;

int n;
int qty[N], tmp[N];
int a[N], b[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> qty[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    int ans = 0;
    for (int i = 0; i <= 2e6; i++) {
        bool flag = true;
        int b_cnt = (1LL << 31) - 1;

        for (int j = 1; j <= n; j++) {
            if ((i64)a[j] * i > qty[j]) {
                flag = false;
                break;
            }

            if (b[j])
                b_cnt = min(b_cnt, (qty[j] - a[j] * i) / b[j]);
        }

        if (flag)
            ans = max(ans, i + b_cnt);
    }

    cout << ans << endl;
    return fflush(stdout), 0;
}
