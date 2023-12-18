#include <iostream>

using namespace std;
using lng = long long;

const int N = 2e6 + 10;

int n;
string s;
int f[N], g[N][26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    s = " " + s;

    lng ans = 0;
    for (int i = 1; i <= n; i++) {
        int idx = s[i] - 'a';
        int lst = g[i - 1][idx] - 1;
        if (lst >= 0) {
            f[i] = f[lst] + 1;
            ans += f[i];
            for (int j = 0; j < 26; j++)
                g[i][j] = g[lst][j];
        }
        g[i][idx] = i;
    }

    cout << ans << endl;
    return 0;
}
