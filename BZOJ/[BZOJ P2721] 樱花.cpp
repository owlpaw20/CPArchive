#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int n;
bool not_prime[N];
int factor[N], expo[N];  // 最小质因子及其指数
vector<int> primes;

void sieve(int x) {  // 线性筛
    for (int i = 2; i <= x; i++) {
        if (!not_prime[i])
            factor[i] = i, primes.push_back(i);
        for (int j : primes) {
            if (i * j > x) break;
            factor[i * j] = j;
            not_prime[i * j] = true;
            if (i % j == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    sieve(n);  // 计算 1~N 的最小质因子

    for (int i = 1; i <= n; i++)
        for (int j = i; j != 1; j /= factor[j])
            expo[factor[j]]++;  // 得到最小质因子的指数

    int ans = 1;
    for (int i = 1; i <= n; i++)
        ans = (i64)ans * (expo[i] * 2 + 1) % MOD;  // 计算 N^2 的约数个数

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
