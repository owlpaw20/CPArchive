#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 5e4 + 5;

int n;
PII seg[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> seg[i].first >> seg[i].second;

    sort(seg + 1, seg + n + 1);
    seg[n + 1] = PII(1e9, 1e9);

    for (int i = 1, l = -1, r = -1; i <= n + 1; i++)
        if (r < seg[i].first) {
            if (l != -1) cout << l << ' ' << r << endl;
            l = seg[i].first;
            r = seg[i].second;
        } else
            r = max(r, seg[i].second);

    return fflush(stdout), 0;
}
