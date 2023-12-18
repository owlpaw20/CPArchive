#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

double maxn, ans, d2, t, d1, c, p;
int n;

struct node {
    double pp, d;
} a[10];

int work(int x) {
    int cc = -1;

    for (int i = x + 1; i <= n && a[i].d - a[x].d <= maxn; i++) {
        if (a[i].pp < a[x].pp) {
            ans += ((a[i].d - a[x].d - t) / d2) * a[x].pp;
            t = 0;
            return i;
        }
        if (cc == -1 || a[i].pp < a[cc].pp)
            cc = i;
    }

    if (d1 - a[x].d <= maxn) {
        ans += ((d1 - a[x].d - t) / d2) * a[x].pp;
        return 1e9;
    }

    if (cc == -1)
        return -1;

    ans += c * a[x].pp;
    t += (maxn - a[cc].d + a[x].d);
    return cc;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(2);
    cout << fixed;

    cin >> d1 >> c >> d2 >> p >> n;

    a[0].d = 0;
    a[0].pp = p;

    for (int i = 1; i <= n; i++)
        cin >> a[i].d >> a[i].pp;

    maxn = c * d2;
    int t = 0;

    while (t != 1e9) {
        t = work(t);
        if (t == -1) {
            cout << "No Solution" << endl;
            return 0;
        }
    }

    cout << ans << endl;
    return 0;
}
