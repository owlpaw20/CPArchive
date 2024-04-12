#include <cmath>
#include <iostream>

#define endl '\n'

using namespace std;

const double eps = 1e-4;
double a, b, c, d, l, r, mid;

double f(double x) {
    return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed;
    cout.precision(2);

    cin >> a >> b >> c >> d;

    for (int i = -100; i < 100; i++) {
        l = i, r = i + 1;
        if (fabs(f(l)) < eps)
            cout << l << ' ';
        else if (fabs(f(r)) < eps)
            continue;
        else if (f(l) * f(r) < 0) {
            while (r - l > eps) {
                mid = (l + r) / 2;
                if (f(mid) * f(r) < 0)
                    l = mid;
                else
                    r = mid;
            }
            cout << l << ' ';
        }
    }

    cout.put('\n');
    fflush(stdout);
    return 0;
}
