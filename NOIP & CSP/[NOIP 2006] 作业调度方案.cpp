#include <iostream>

#define endl '\n'

using namespace std;

int m, n;
int list[625];
int step[25];
int las_time[25];
int mac[25][100086];

struct node {
    int id, cost;
} a[25][25];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for (int i = 1; i <= m * n; i++)
        cin >> list[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j].id;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j].cost;

    int ans = 0;
    for (int i = 1; i <= m * n; i++) {
        int now = list[i];
        step[now]++;
        int id = a[now][step[now]].id, cost = a[now][step[now]].cost, s = 0;
        for (int j = las_time[now] + 1;; j++) {
            if (mac[id][j] == 0) s++;
            else s = 0;
            if (s == cost) {
                for (int k = j - cost + 1; k <= j; k++) mac[id][k] = 1;
                if (j > ans) ans = j;
                las_time[now] = j;
                break;
            }
        }
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
