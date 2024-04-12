#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 3e2 + 5;

int N, M;
int f[MAX_N][MAX_N];
// f[u][i][j] 表示以 u 为根的子树中在前 i 个节点中选 j 门课的方案数
// 滚动数组优化掉了 i 这一维

int ed[MAX_N], nx[MAX_N], head[MAX_N], idx;

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

void DP(int u) {
    for (int i = head[u]; ~i; i = nx[i]) {
        DP(ed[i]);
        for (int j = M + 1; j; --j)      // 枚举所选课数
            for (int k = 0; k < j; ++k)  // 枚举当前节点所学习的课程数
                f[u][j] = std::max(f[u][j], f[ed[i]][k] + f[u][j - k]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    memset(head, -1, sizeof head);

    std::cin >> N >> M;
    for (int i = 1, k, s; i <= N; ++i) {
        std::cin >> k >> s;
        f[i][1] = s;  // 当前节点的子树中只学习一门课，则一定只能为树根
        connect(k, i);
    }

    DP(0);

    std::cout << f[0][M + 1] << endl;
    return fflush(stdout), 0;
}
