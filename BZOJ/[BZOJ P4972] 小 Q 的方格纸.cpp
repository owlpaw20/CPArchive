#include <iostream>

#define endl '\n'

using namespace std;
using u32 = unsigned int;

const u32 N = 3e3 + 5;
const u32 Q = 3e6 + 5;

u32 n, m, q, A, B, C;
u32 p233[Q], a[N][N];
u32 suf1[N][N], suf2[N][N];

u32 rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    u32 t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}

void prep(int n) {
    p233[0] = 1;
    for (int i = 1; i <= n; i++)
        p233[i] = p233[i - 1] * 233;
}

u32 solve(int x, int y, int k) {
    return suf2[x][y - k + 1] - suf2[x - k][y + 1] - suf1[x][y + 1] + suf1[x - k][y + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    cin >> A >> B >> C;

    for (u32 i = 1; i <= n; i++) {
        for (u32 j = 1; j <= m; j++)
            a[i][j] = rng61();
        for (u32 j = m; j >= 1; j--) {
            suf1[i][j] = suf1[i - 1][j] + suf1[i][j + 1] - suf1[i - 1][j + 1] + a[i][j];
            suf2[i][j] = suf2[i][j + 1] + suf2[i - 1][j + 1] - suf2[i - 1][j + 2] + a[i][j];
        }
    }

    prep(q);

    u32 ans = 0;
    for (u32 i = 1, x, y, k; i <= q; i++) {
        x = rng61() % n + 1;
        y = rng61() % m + 1;
        k = rng61() % min(x, y) + 1;

        ans += solve(x, y, k) * p233[q - i];
    }

    cout << ans << endl;
    return fflush(stdout), 0;
}
