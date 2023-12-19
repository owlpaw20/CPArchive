#include <vector>
#include <climits>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

const int N = 1e6 + 10;

lng L, R;
bool composite[N];
vector<lng> primes;
vector<lng> r_primes;

void prep(int n) {
    for (int i = 2; i <= n; i++) {
        if (!composite[i])
            primes.push_back(i);
        for (int p : primes) {
            if (i * p > n) break;
            composite[i * p] = true;
            if (i % p == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    prep((1 << 16) + 10);

    while (cin >> L >> R) {
        r_primes.clear();
        memset(composite, false, sizeof composite);

        for (lng p : primes)
            for (lng i = max(p * 2, (L + p - 1) / p * p); i <= R; i += p)
                composite[i - L] = true;

        for (int i = 0; i <= R - L; i++)
            if (!composite[i] && i + L > 1)
                r_primes.push_back(i + L);

        if (r_primes.size() < 2) {
            puts("There are no adjacent primes.");
            continue;
        }

        int min_prime = r_primes[0];
        int max_prime = r_primes[0];
        int min_delta = r_primes[1] - r_primes[0];
        int max_delta = r_primes[1] - r_primes[0];

        for (int i = 0; i + 1 < r_primes.size(); i++) {
            int delta = r_primes[i + 1] - r_primes[i];
            if (delta < min_delta)
                min_delta = delta, min_prime = r_primes[i];
            if (delta > max_delta)
                max_delta = delta, max_prime = r_primes[i];
        }

        printf("%d,%d are closest, %d,%d are most distant.\n",
            min_prime, min_prime + min_delta,
            max_prime, max_prime + max_delta);
    }

    fflush(stdout);
    return 0;
}
