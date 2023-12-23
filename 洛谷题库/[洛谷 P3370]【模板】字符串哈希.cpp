#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int BASE = 131, N = 1e4 + 10;
int n, ans = 1;
string s;
ull flag[N];

ull get_hash(string s) {
    int len = s.length();
    ull res = 0;
    for (int i = 0; i < len; i++)
        res = res * BASE + s[i];
    return res;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        flag[i] = get_hash(s);
    }
    sort(flag + 1, flag + n + 1);
    for (int i = 2; i <= n; i++)
        if (flag[i] != flag[i - 1])
            ans++;
    cout << ans << endl;
    return 0;
}
