#include <iostream>

#define endl '\n'

using namespace std;

const int N = 5e2 + 5;

char steps[N];
char mp[N][N];

int n, m, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;
    for (int i = 1; i <= K; i++) cin >> steps[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> mp[i][j];

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int x = i, y = j;
            bool flag = true;

            if (mp[x][y] == '#')
                flag = false;
            else {
                for (int k = 1; k <= K; k++) {
                    int tx = x, ty = y;
                    if (steps[k] == 'L')
                        ty -= 1;
                    else if (steps[k] == 'R')
                        ty += 1;
                    else if (steps[k] == 'U')
                        tx -= 1;
                    else
                        tx += 1;

                    if (tx < 1 || tx > n || ty < 1 || ty > m || mp[tx][ty] == '#') {
                        flag = false;
                        break;
                    }

                    x = tx, y = ty;
                }
            }

            ans += flag;
        }

    cout << ans << endl;
    return fflush(stdout), 0;
}
