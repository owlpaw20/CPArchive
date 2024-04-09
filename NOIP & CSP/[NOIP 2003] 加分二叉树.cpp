#include <vector>
#include <iostream>

#define endl '\n'

using u32 = unsigned int;

const int MAX_N = 35;

int N, val[MAX_N];
u32 f[MAX_N][MAX_N];
int root[MAX_N][MAX_N];

void iterate(const int l, const int r) {
    if (l > r) return;
    std::cout << root[l][r] << ' ';
    iterate(l, root[l][r] - 1);
    iterate(root[l][r] + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;
    for (int i = 1; i <= N; ++i) std::cin >> val[i];

    for (int len = 1; len <= N; ++len)
        for (int l = 1, r = len; r <= N; ++l, ++r)
            for (int k = l; k <= r; ++k) {
                int lt = (k == l) ? 1 : f[l][k - 1];
                int rt = (k == r) ? 1 : f[k + 1][r];
                u32 pts = (l != r) * lt * rt + val[k];

                if (pts > f[l][r]) {
                    f[l][r] = pts;
                    root[l][r] = k;
                }
            }

    std::cout << f[1][N] << endl;
    iterate(1, N);

    return fflush(stdout), 0;
}
