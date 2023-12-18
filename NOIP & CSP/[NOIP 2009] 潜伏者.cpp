#include <string>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 128;

string a, b, c;
char cd[N], dc[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(cd, '#', sizeof cd);
    memset(dc, '#', sizeof dc);

    cin >> a >> b >> c;

    if (a.length() < 26)
        return puts("Failed") && 0;

    int len = a.length();
    for (int i = 0; i < len; i++) {
        if (dc[b[i]] != a[i] && dc[b[i]] != '#')
            return puts("Failed") && 0;
        cd[a[i]] = b[i];
        dc[b[i]] = a[i];
    }

    for (char i = 'A'; i <= 'Z'; i++)
        if (cd[i] == '#' || dc[i] == '#')
            return puts("Failed") && 0;

    for (char ch : c)
        putchar(cd[ch]);

    putchar('\n');
    fflush(stdout);
    return 0;
}
