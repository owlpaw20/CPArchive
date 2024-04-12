#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 15;
const int M = 1 << 12;
const int MOD = 1e8;

int n, m;
int row[N];
int f[N][M];

vector<int> states;
vector<int> head[M];

bool check(int st) {
    for (int i = 0; i + 1 < m; i++)
        if ((st >> i) & 1 and (st >> (i + 1)) & 1)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++) {
            bool cell;
            cin >> cell;
            if (!cell) row[i] += (1 << j);  // 将无法种植的土地事先标记好
        }

    for (int i = 0; i < (1 << m); i++)  // 枚举一行中所有可能的状态
        if (check(i))                   // 检查当前状态在水平方向上是否合法
            states.push_back(i);        // 如果合法则存储

    for (int st : states)
        for (int ts : states)
            if ((st & ts) == 0)          // 如果这两个行上的状态之间从纵向上看也是合法的
                head[st].push_back(ts);  // 标记后者可以通过前者转移得到

    f[0][0] = 1;  // 不种植也是一种方案

    for (int i = 1; i <= n + 1; i++)     // 枚举所有行并在最后一行保存结果
        for (int st : states)            // 枚举当前行所有合法的状态
            if ((st & row[i]) == 0)      // 如果与无法种植的土地没有冲突
                for (int ts : head[st])  // 则遍历从上一行到当前行的所有合法转移并更新状态数量
                    f[i][st] = (f[i][st] + f[i - 1][ts]) % MOD;

    cout << f[n + 1][0] << endl;  // 结果保存在最后一行
    fflush(stdout);
    return 0;
}
