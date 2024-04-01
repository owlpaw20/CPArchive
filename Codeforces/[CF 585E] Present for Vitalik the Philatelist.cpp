// 参考题解：https://codeforces.com/blog/entry/20898
// 参考题解：https://www.luogu.com.cn/article/40qvmq0u

#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 5e5 + 5;
const int V1 = 1e7;
const int V2 = 1e7 + 5;
const int MOD = 1e9 + 7;

int n;
int a[N]; // 邮票
int mu[V2]; // 容斥系数
int t[V2]; // 存储邮票价值的出现次数
int b[V2]; // 价值为 i 的倍数的邮票个数
int p2[N]; // 预处理 2 的幂
int f[N]; // 预处理组合数，f[x] = 2f[x - 1] + 2^(x - 1)

// 根据欧拉筛枚举质数倍数的结果来预处理容斥系数
bool flag[V2];
vector<int> primes;

void Eulers_sieve() {
    for (int i = 2; i <= V1; i++) {
        if (!flag[i])
            primes.push_back(i), mu[i] = -1;
        for (int j : primes) {
            if (i * j > V2) break;
            flag[i * j] = true;
            if (i % j == 0) {
                mu[i * j] = 0;
                break;
            }
            mu[i * j] = -mu[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i], t[a[i]]++;

    /*
        当 mu[d] = 0 时，d 为某质数平方后的倍数，不需要统计，即 * 0
        当 mu[d] = 1 时，d 能被分解为偶数个质因子，需要统计一次，即 * 1
        当 mu[d] = -1 时，d 能被分解为奇数个质因子，多统计了一次，需要减掉，即 * -1
    */

    mu[1] = 1;
    Eulers_sieve();

    // 暴力枚举统计价值为 i 的倍数的邮票个数
    for (int i = 1; i <= V1; i++)
        for (int j = i; j <= V1; j += i)
            b[i] += t[j];

    // 处理 2 的次幂和组合数
    p2[0] = 1;
    for (int i = 1; i <= n; i++) {
        p2[i] = (p2[i - 1] << 1) % MOD;
        f[i] = ((f[i - 1] << 1) % MOD + p2[i - 1]) % MOD;
    }

    i64 ans = 0;
    for (int d = 1; d <= V1; d++) {
        ans = (ans + mu[d] * (f[b[d]] - b[d])) % MOD; // 加上前一半式子
        ans = ((ans - mu[d] * ((i64)n * (p2[b[d]] - 1) - f[b[d]])) % MOD + MOD) % MOD; // 减去后一半式子
    }

    cout << ans << endl;
    return fflush(stdout), 0;
}
