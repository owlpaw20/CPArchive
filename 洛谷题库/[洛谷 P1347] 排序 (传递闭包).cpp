#include <cctype>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 30;

int n, m;
bool vis[N];
bool g[N][N];
bool tmp[N][N];

void compute_transitive_closure(int n) {
    memcpy(tmp, g, sizeof tmp);
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                tmp[i][j] |= (tmp[i][k] & tmp[k][j]);
}

int try_ensure(int n) {
    for (int i = 1; i <= n; i++)
        if (tmp[i][i]) // 如果出现一个环（自己与自己连通）
            return -1; // 则说明出现了矛盾

    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (!tmp[i][j] && !tmp[j][i]) // 只要还存在任意一组未建立关系的变量
                return 0; // 就说明还没有完全确定

    return 1; // 以上两种情况之外就说明已经找到
}

vector<char> get_topological_sequence(int n) {
    memset(vis, false, sizeof vis);
    vector<char> path;

    while ((int)path.size() < n) { // 如果没有装入全部节点就一直循环
        for (int i = 1; i <= n; i++) { // 每次找到第一个出现矛盾的节点加入序列中
            if (vis[i]) continue;
            bool flag = true;
            for (int j = 1; j <= n; j++)
                if (!vis[j] && g[j][i]) { // 从 j 到 i 有连边
                    flag = false; // 表明 j 节点的值小于 i 节点
                    break; // 所以 i 节点一定不是当前最小值
                }
            if (flag) {
                vis[i] = true;
                path.push_back(i + 'A' - 1);
            }
        }
    }
    return path;
}

void solve(int n, int m) {
    memset(g, false, sizeof g);

    int ensured = 0, when = -1;
    for (int i = 1, a, b; i <= m; i++) {
        char cha, cho, chb;
        cin >> cha >> cho >> chb;
        a = cha - 'A' + 1;
        b = chb - 'A' + 1;

        if (ensured == 0) {
            g[a][b] = true;
            compute_transitive_closure(n); // 计算传递闭包
            ensured = try_ensure(n); // 保存是否可以确认目标
            if (ensured != 0)
                when = i;
        }
    }

    if (ensured == 0)
        puts("Sorted sequence cannot be determined.");

    else if (ensured == 1) {
        printf("Sorted sequence determined after %d relations: ", when);
        vector<char> ans = get_topological_sequence(n);
        for (char ch : ans) putchar(ch);
        putchar('.'), putchar('\n');
    } else
        printf("Inconsistency found after %d relations.\n", when);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    solve(n, m);

    fflush(stdout);
    return 0;
}
