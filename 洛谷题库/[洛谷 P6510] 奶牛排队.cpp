#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;

const int MAX_N = 1e5 + 5;

int N, a[MAX_N];
int tmn, tmx, smn[MAX_N], smx[MAX_N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> a[i];

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        while (tmn && a[smn[tmn]] >= a[i]) --tmn;
        while (tmx && a[smx[tmx]] < a[i]) --tmx;
        int pos = std::upper_bound(smn + 1, smn + tmn + 1, smx[tmx]) - smn;
        if (pos != tmn + 1) ans = std::max(ans, i - smn[pos] + 1);
        smn[++tmn] = smx[++tmx] = i;
    }

    cout << ans << endl;
    return fflush(stdout), 0;
}
