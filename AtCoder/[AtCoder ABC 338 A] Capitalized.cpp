#include <cctype>
#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    bool flag = true;
    if (!isupper(s.front())) flag = false;

    for (int i = 1; i < (int)s.length(); i++)
        flag &= !isupper(s[i]);

    if (flag)
        puts("Yes");
    else
        puts("No");
    return fflush(stdout), 0;
}
