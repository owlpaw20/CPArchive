#include <string>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

i64 n;

bool check(i64 x) {
    string s = to_string(x);
    return string(s.begin(), s.end()) == string(s.rbegin(), s.rend());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    i64 ans = -1;
    for (i64 i = 1; i * i * i <= n; i++)
        if (check(i * i * i))
            ans = i * i * i;

    cout << ans << endl;
    return fflush(stdout), 0;
}
