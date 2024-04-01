#include <cstring>
#include <iostream>
using namespace std;

const int N = 60;
const int M = 510;
const char block[6][8] = {
    "..+---+",
    "./   /|",
    "+---+ |",
    "|   | +",
    "|   |/.",
    "+---+.."
};

int m, n, b[N][N];
char g[M][M];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> b[i][j];
    memset(g, '.', sizeof g);
    int top = 500, right = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 0; k < b[i][j]; k++) {
                int tx = 500 - 2 * (n - i) - 3 * k;
                int ty = 2 * (n - i) + 4 * (j - 1) + 1;
                top = min(top, tx - 5);
                right = max(right, ty + 6);
                for (int p = 0; p < 6; p++)
                    for (int q = 0; q < 7; q++)
                        if (block[p][q] != '.')
                            g[tx - 5 + p][ty + q] = block[p][q];
            }
    for (int i = top; i <= 500; i++) {
        for (int j = 1; j <= right; j++)
            cout << g[i][j];
        cout << endl;
    }
    return 0;
}
