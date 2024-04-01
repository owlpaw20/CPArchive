#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;
using PII = pair<int, int>;

const int N = 5e2 + 10;
const int INF = 0x3F3F3F3F;

int n, m;
int g[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(g, 0x3F, sizeof g);

    cin >> m >> n;

    string line;
    getline(cin, line); // 读入上一行的换行符
    while (m--) {
        getline(cin, line);
        stringstream ssin(line);
        vector<int> stop;

        int t;
        while (ssin >> t) stop.push_back(t);
        for (int i = 0; i < stop.size(); i++)
            for (int j = i + 1; j < stop.size(); j++)
                g[stop[i]][stop[j]] = 1;
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

    if (g[1][n] == INF) puts("NO");
    else cout << g[1][n] - 1 << endl;
    return 0;
}
