#include <limits>
#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;

using u32 = unsigned int;

const int MAX_N = 2e5 + 5;
const int CASES = 1 << 3;

u32 N, x[MAX_N], y[MAX_N], z[MAX_N];
u32 max[CASES];

void prep() {
    for (u32 i = 0; i < CASES; i++)
        for (u32 j = 1, sum; j <= N; j++) {
            sum = (i >> 0 & 1) ? x[j] : 0;
            sum += (i >> 1 & 1) ? y[j] : 0;
            sum += (i >> 2 & 1) ? z[j] : 0;
            max[i] = std::max(max[i], sum);
        }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (u32 i = 1; i <= N; i++)
        cin >> x[i] >> y[i] >> z[i];

    prep();

    u32 ans1 = std::numeric_limits<u32>::max(), ans2 = 0;
    for (u32 i = 1, cost; i <= N; i++) {
        cost = 0;

        for (u32 j = 0, sum; j < CASES; j++) {
            sum = (j >> 0 & 1) ? x[i] : 0;
            sum += (j >> 1 & 1) ? y[i] : 0;
            sum += (j >> 2 & 1) ? z[i] : 0;
            cost = std::max(cost, max[j] - sum);
        }

        if (cost < ans1) ans1 = cost, ans2 = i;
    }

    cout << ans1 << ' ' << ans2 << endl;
    return fflush(stdout), 0;
}
