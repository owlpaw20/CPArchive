#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;

int n, p[N], g[N], h[N];

struct House {
    int s, a;
    bool operator<(const House& t) const { return a > t.a; }
} v[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i].s;
    for (int i = 1; i <= n; i++) cin >> v[i].a;

    sort(v + 1, v + 1 + n);

    for (int i = 1; i <= n; i++) {
        p[i] = p[i - 1] + v[i].a;
        g[i] = max(g[i - 1], 2 * v[i].s);
    }
    for (int i = n; i >= 1; i--)
        h[i] = max(h[i + 1], 2 * v[i].s + v[i].a);

    for (int i = 1; i <= n; i++)
        cout << max(p[i] + g[i], p[i - 1] + h[i]) << endl;

    return 0;
}
