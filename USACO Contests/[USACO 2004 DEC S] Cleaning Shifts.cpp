#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 3e4 + 10;

int n, T;
PII se[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T;
    for (int i = 1; i <= n; i++)
        cin >> se[i].first >> se[i].second;

    sort(se + 1, se + n + 1);

    int l = 1, ans = 0;
    int i = 1, j = 1;

    while (i <= n) {
        int r = 0;
        while (j <= n && se[j].first <= l)
            r = max(se[j++].second, r);
        if (r < l) break;
        ans++;
        if (r >= T) {
            cout << ans << endl;
            exit(0);
        }
        l = r + 1, i = j;
    }

    cout << -1 << endl;
    fflush(stdout);
    return 0;
}
