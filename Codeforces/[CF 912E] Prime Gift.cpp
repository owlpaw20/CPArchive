#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>

using u64 = unsigned long long;
using u128 = unsigned __int128;

const int MAX_N = 20;
const u64 MAX_V = 1e18;
const int CAPACITY = 2e6 + 5;

int N, p[MAX_N], K;
std::vector<u64> set_A, set_B;

void DFS_set_A(const int i, u128 prod) {
    set_A.push_back(prod);
    if (i > N) return;

    do {
        DFS_set_A(i + 2, prod);
        prod *= p[i];
    } while (prod <= MAX_V);
}

void DFS_set_B(const int i, u128 prod) {
    set_B.push_back(prod);
    if (i > N) return;

    do {
        DFS_set_B(i + 2, prod);
        prod *= p[i];
    } while (prod <= MAX_V);
}

bool check(const u64 x) {
    int cnt = 0;
    int b = set_B.size() - 1;

    for (const u64 a : set_A) {
        while (~b && a * set_B[b] > x) --b;
        cnt += b + 1;
    }

    return cnt >= K;
}

int main() {
    scanf("%d\n", &N);
    for (int i = 1; i <= N; ++i) scanf("%d ", &p[i]);

    scanf("%d\n", &K);

    set_A.reserve(CAPACITY);
    set_B.reserve(CAPACITY);

    DFS_set_A(1, 1);
    DFS_set_B(2, 1);

    std::sort(set_A.begin(), set_A.end());
    std::sort(set_B.begin(), set_B.end());
    set_A.erase(std::unique(set_A.begin(), set_A.end()), set_A.end());
    set_B.erase(std::unique(set_B.begin(), set_B.end()), set_B.end());

    u64 l = 0, r = MAX_V, mid;
    while (l < r)
        check(mid = (l + r) >> 1) ? (r = mid) : (l = mid + 1);

    printf("%llu\n", r);
    return fflush(stdout), 0;
}
