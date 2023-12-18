#include <iostream>

#define endl '\n'

using namespace std;

int n, t;
int nodeCnt, bestCnt, maxp = -1;
int mine[25], best[25], path[25];
bool map[25][25];

void dfs(int x, int sum) {
    for (int i = x + 1; i <= n; i++)
        if (map[x][i]) {
            path[++nodeCnt] = i;
            dfs(i, sum + mine[i]);
            nodeCnt--;
        }
    if (sum > maxp) {
        maxp = sum;
        for (int i = 1; i <= nodeCnt; i++)
            best[i] = path[i];
        bestCnt = nodeCnt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> mine[i];
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            cin >> t;
            map[i][j] = t;
        }

    for (int i = 1; i <= n; i++) {
        path[++nodeCnt] = i;
        dfs(i, mine[i]);
        nodeCnt--;
    }

    for (int i = 1; i <= bestCnt; i++)
        cout << best[i] << " ";

    cout << endl;
    cout << maxp << endl;
    fflush(stdout);
    return 0;
}
