#include <iostream>

#define endl '\n'

const int MAX_N = 1e2 + 5;
const int MAX_H = 2e3;

int N;
int h[MAX_N];
bool f[MAX_H + 5][MAX_H + 5];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;
    for (int i = 1; i <= N; ++i) std::cin >> h[i];

    f[0][0] = true;

    for (int k = 1; k <= N; ++k)
        for (int i = MAX_H; ~i; --i)
            for (int j = MAX_H; ~j; --j) {
                if (i >= h[k]) f[i][j] |= f[i - h[k]][j];
                if (j >= h[k]) f[i][j] |= f[i][j - h[k]];
            }

    for (int i = MAX_H; i; --i)
        if (f[i][i]) {
            std::cout << i << endl;
            return fflush(stdout), 0;
        }

    std::cout << "Impossible" << endl;
    return fflush(stdout), 0;
}
