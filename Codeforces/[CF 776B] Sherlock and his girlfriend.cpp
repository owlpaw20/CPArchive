#pragma GCC optimize("O2")
#include <vector>
#include <iostream>

using namespace std;

int n;
vector<int> primes;
vector<bool> not_prime;

void get_primes(int n) {
    not_prime.assign(n + 5, false);
    not_prime[0] = not_prime[1] = true;

    for (int i = 2; i <= n; i++) {
        if (!not_prime[i])
            primes.push_back(i);
        for (int p : primes) {
            if (i * p > n) break;
            not_prime[i * p] = true;
            if (i % p == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    get_primes(n + 1);

    cout << (n <= 2 ? 1 : 2) << '\n';

    for (int i = 2; i <= n + 1; i++)
        cout << not_prime[i] + 1 << ' ';

    cout.put('\n');

    fflush(stdout);
    return 0;
}
