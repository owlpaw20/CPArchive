#include <vector>
#include <iostream>

using namespace std;
using i64 = long long;

const int N = 1e6 + 10;
const int M = 8e4 + 10;  // [1, 1e6] 上共有 78498 个素数
const int MOD = 666623333;

i64 l, r;
bool not_prime[N];
i64 vis[N], phi[N];
vector<i64> primes;

void prep() {
    primes.reserve(M);
    for (int i = 2; i <= 1e6; i++) {
        if (!not_prime[i]) primes.push_back(i);
        for (int j = 2 * i; j <= 1e6; j += i)
            not_prime[j] = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    prep();

    cin >> l >> r;
    for (i64 i = l; i <= r; i++)
        vis[i - l] = i, phi[i - l] = i;

    for (i64 p : primes) {
        if (p * p > r) break;
        i64 start = l;
        if (l % p) start = l / p * p + p;
        for (i64 i = start; i <= r; i += p) {
            phi[i - l] = phi[i - l] / p * (p - 1);
            while (vis[i - l] % p == 0)
                vis[i - l] /= p;
        }
    }

    i64 ans = 0;
    for (i64 i = l; i <= r; i++) {
        if (vis[i - l] > 1)
            phi[i - l] = phi[i - l] / vis[i - l] * (vis[i - l] - 1);
        ans = (ans + (i - phi[i - l]) % MOD) % MOD;
    }

    cout << ans << endl;
    return 0;
}
