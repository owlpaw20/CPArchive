#include <limits>
#include <iostream>

#define endl '\n'

const int MAX_N = 55;

int N, C, ans = std::numeric_limits<int>::max();
int pos[MAX_N], power[MAX_N];
bool vis[MAX_N];

int remain;

void DFS(const int idx, int consumed) {
    if (consumed > ans) return;

    int pre = idx, nxt = idx;
    bool is_on = false;

    while (pre > 1 && vis[pre]) --pre;
    while (nxt < N && vis[nxt]) ++nxt;

    if (!vis[pre]) {
        vis[pre] = true;
        consumed += remain * (pos[idx] - pos[pre]);
        remain -= power[pre];
        DFS(pre, consumed);
        vis[pre] = false;
        remain += power[pre];
        consumed -= remain * (pos[idx] - pos[pre]);
        is_on = true;
    }

    if (!vis[nxt]) {
        vis[nxt] = true;
        consumed += remain * (pos[nxt] - pos[idx]);
        remain -= power[nxt];
        DFS(nxt, consumed);
        vis[nxt] = false;
        remain += power[nxt];
        consumed -= remain * (pos[nxt] - pos[idx]);
        is_on = true;
    }

    if (!is_on) ans = std::min(ans, consumed);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> C;
    for (int i = 1; i <= N; ++i)
        std::cin >> pos[i] >> power[i], remain += power[i];

    remain -= power[C];
    vis[C] = true;

    DFS(C, 0);

    std::cout << ans << endl;
    return fflush(stdout), 0;
}
