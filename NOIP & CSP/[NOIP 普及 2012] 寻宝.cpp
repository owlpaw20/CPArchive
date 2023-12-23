#include <iostream>
using namespace std;

const int N = 1e5 + 10;
const int M = 1e2 + 10;
const int MOD = 20123;

struct Room {
    bool flag;
    int num;
};

int n, m, st, ans, b[N];
Room p[N][M];

void read(int i, int j) {
    cin >> p[i][j].flag >> p[i][j].num;
    if (p[i][j].flag) b[i]++;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
            read(i, j);
    cin >> st;
    for (int i = 1; i <= n; i++) {
        ans = (p[i][st].num + ans) % MOD;
        int cnt = p[i][st].num % b[i];
        if (cnt == 0) cnt = b[i];
        if (p[i][st].flag) cnt--;
        while (cnt) {
            st = (st + 1) % m;
            if (p[i][st].flag) cnt--;
        }
    }
    cout << ans << endl;
    return 0;
}
