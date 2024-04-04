#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using u64 = uint64_t;

const int MAX_N = 1e2 + 5;
const u64 BASE = 1311313331;

int N;
u64 ans[MAX_N][MAX_N];

int ed[MAX_N], nx[MAX_N], head[MAX_N], idx;

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

u64 tree_hash(int u, int fa) {
    std::vector<u64> q;

    for (int i = head[u]; ~i; i = nx[i])
        if (ed[i] != fa)
            q.push_back(tree_hash(ed[i], u));

    std::sort(q.begin(), q.end());

    u64 ans = MAX_N;

    for (u64 t : q)
        ans = ans * BASE + t;

    return ans * BASE + MAX_N + 1;
}

void solve(int c) {
    std::cin >> N;
    for (int i = 1, t; i <= N; ++i) {
        std::cin >> t;
        if (t) connect(i, t), connect(t, i);
    }

    for (int i = 1; i <= N; ++i) ans[c][i] = tree_hash(i, 0);
    std::sort(ans[c] + 1, ans[c] + N + 1);

    for (int i = 1, j = 0; i <= c; ++i) {
        while (j++ <= N)
            if (ans[c][j] != ans[i][j])
                break;

        if (j > N) {
            std::cout << i << endl;
            break;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    for (int C = 1; C <= T; ++C) {
        memset(head, -1, sizeof head);
        memset(ed, 0, sizeof ed);
        memset(nx, 0, sizeof nx);
        idx = 0;
        solve(C);
    };

    return fflush(stdout), 0;
}
