#include <cstring>
#include <iostream>

#define endl '\n'

const int MAX_N = 4e2 + 5;
const int MAX_V = 8e5 + 5;
const int SHIFT = 4e5;

int N;
int IQ[MAX_N], EQ[MAX_N];
int f[MAX_V];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    memset(f, 0xCF, sizeof f);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
        std::cin >> IQ[i] >> EQ[i];

    f[SHIFT] = 0;

    for (int i = 1; i <= N; ++i)
        if (IQ[i] >= 0)
            for (int j = SHIFT << 1; j >= IQ[i]; --j)
                f[j] = std::max(f[j], f[j - IQ[i]] + EQ[i]);
        else
            for (int j = 0; j <= (SHIFT << 1) + IQ[i]; ++j)
                f[j] = std::max(f[j], f[j - IQ[i]] + EQ[i]);

    int ans = 0;

    for (int i = SHIFT; i <= (SHIFT << 1); ++i)
        if (f[i] > 0)
            ans = std::max(ans, f[i] + i - SHIFT);

    std::cout << ans << endl;
    return fflush(stdout), 0;
}
