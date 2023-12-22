#include <cctype>
#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

int row[9][10];
int col[9][10];
int sub[3][3][10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    for (int i = 1, r = 0, c = 0; i <= 13; i++) {
        cin >> s;
        if (i % 4 == 1) continue;
        for (char ch : s) {
            if (c >= 9) c = 0, r++;
            if (isdigit(ch)) {
                row[r][ch - '0']++;
                col[c][ch - '0']++;
                sub[r / 3][c / 3][ch - '0']++;
                c++;
            } else if (ch == '.')
                c++;
        }
    }

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 10; j++)
            if (row[i][j] > 1 || col[i][j] > 1 || sub[i / 3][i % 3][j] > 1)
                return puts("GRESKA"), 0;

    puts("OK");
    fflush(stdout);
    return 0;
}
