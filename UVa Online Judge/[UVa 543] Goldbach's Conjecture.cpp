#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int t, idx, P[N];
bool not_prime[N] = {1, 1};

void prep(int x) {
    for (int i = 2; i <= x; i++) {
        if (!not_prime[i])
            P[idx++] = i;
        for (int p : P) {
            if (i * p > x) break;
            not_prime[i * p] = true;
            if (i % p == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    prep(N);

    while (cin >> t && t != 0) {
        for (int p : P)
            if (binary_search(P, P + idx, t - p)) {
                printf("%d = %d + %d\n", t, p, t - p);
                break;
            }
    }
    return 0;
}