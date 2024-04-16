#include <limits>
#include <bitset>
#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 10;
const int MAX_STATES = 1 << (MAX_N << 1);
const int I32_MAX = std::numeric_limits<int>::max();
const int I32_MIN = std::numeric_limits<int>::min();

int N, M;
int a[MAX_N][MAX_N];
int b[MAX_N][MAX_N];

int f[MAX_STATES];
bool vis[MAX_STATES];

int DFS(int state, bool person) {
    if (vis[state]) return f[state];

    vis[state] = true;
    f[state] = person ? I32_MIN : I32_MAX;

    for (int i = 0, x = N, y = 0; i < N + M - 1; ++i) {
        ((state >> i) & 1) ? --x : ++y;
        if (((state >> i) & 3) != 1) continue;

        f[state] = person ? std::max(f[state], DFS(state ^ (3 << i), !person) + a[x][y]) :
                            std::min(f[state], DFS(state ^ (3 << i), !person) - b[x][y]);
    }

    return f[state];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> M;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            std::cin >> a[i][j];

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            std::cin >> b[i][j];

    int st_state = ((1 << N) - 1) << M;
    int fn_state = (1 << N) - 1;
    vis[st_state] = true;
    DFS(fn_state, 1);

    std::cout << f[fn_state] << endl;
    return fflush(stdout), 0;
}
