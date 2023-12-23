#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 1e8 + 10;

int n, q;
bool is_prime[N];
vector<int> prime;

void get_prime(int n) {
    for (int i = 2; i <= n; i++) {
        if (!is_prime[i])
            prime.push_back(i);
        for (auto j : prime) {
            if (i * j > n) break;
            is_prime[i * j] = 1;
            if (i % j == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> q;
    get_prime(n);
    while (q--) {
        int t;
        cin >> t;
        cout << prime[t - 1] << endl;
    }
    return 0;
}
