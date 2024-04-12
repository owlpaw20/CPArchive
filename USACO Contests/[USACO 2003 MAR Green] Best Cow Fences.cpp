#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;

const double EPSILON = 1e-5;

int n, m;
vector<double> cow;
vector<double> pre;

bool check(double x) {
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + cow[i] - x;
    double minval = 0;
    for (int i = m; i <= n; i++) {
        minval = min(minval, pre[i - m]);
        if (pre[i] >= minval)
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cow.resize(n + 1);
    pre.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> cow[i];

    double l = 0, r = 1e5 + 1;
    while (r - l > EPSILON) {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    cout << (int)(r * 1000) << endl;
    fflush(stdout);
    return 0;
}
