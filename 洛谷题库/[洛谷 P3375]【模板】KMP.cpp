#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int N = 1e6 + 10;
int n, m, pi[N];
string s, t;

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t >> s;
    n = s.size(), m = t.size();
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    for (int i = 0, j = 0; i < m; i++) {
        while (j > 0 && t[i] != s[j]) j = pi[j - 1];
        if (t[i] == s[j]) j++;
        if (j == n) {
            cout << i - j + 2 << endl;
            j = pi[j - 1];
        }
    }
    for (int i = 0; i < n; i++)
        cout << pi[i] << " ";
    cout << endl;
    return 0;
}
