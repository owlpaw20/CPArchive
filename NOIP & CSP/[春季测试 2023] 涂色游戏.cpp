#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

int T, n, m, p, opt, x, c;

struct node {
    int replaced, color;
} row[100001], col[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);

        cin >> n >> m >> p;

        for (int i = 1; i <= p; i++) {
            cin >> opt >> x >> c;
            if (opt == 0) row[x].color = c, row[x].replaced = i;
            else col[x].color = c, col[x].replaced = i;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++)
                cout << (row[i].replaced > col[j].replaced ? row[i].color : col[j].color) << ' ';
            cout << endl;
        }
    }

    fflush(stdout);
    return 0;
}
