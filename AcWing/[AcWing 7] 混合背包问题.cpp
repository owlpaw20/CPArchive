#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 5;

int n, m, f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    while (n--) {
        int c, v, s;
        cin >> c >> v >> s;

        s = abs(s);

        if (s == 0) {
            for (int i = c; i <= m; i++)
                f[i] = max(f[i], f[i - c] + v);
        } else {
            for (int b = 1; b <= s; s -= b, b <<= 1)
                for (int i = m; i >= b * c; i--)
                    f[i] = max(f[i], f[i - b * c] + b * v);
            if (s > 0)
                for (int i = m; i >= s * c; i--)
                    f[i] = max(f[i], f[i - s * c] + s * v);
        }
    }

    cout << f[m] << endl;

    fflush(stdout);
    return 0;
}
