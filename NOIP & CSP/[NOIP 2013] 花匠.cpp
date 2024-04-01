#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;

int n;
int h[N];
int f[N], g[N];

// f[i] = 以 h[i] 为波峰的状态且由 h[i] 结尾的合法序列的长度
// g[i] = 以 h[i] 为波谷的状态且由 h[i] 结尾的合法序列的长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> h[i];

    f[1] = g[1] = 1;

    for (int i = 2; i <= n; i++)
        if (h[i] > h[i - 1]) { // 如果遇到一个波峰
            f[i] = max(f[i - 1], g[i - 1] + 1); // 把波峰接在上一次波谷的后面
            g[i] = g[i - 1]; // 波谷不用更新
        } else if (h[i] == h[i - 1]) {
            f[i] = f[i - 1];
            g[i] = g[i - 1];
        } else { // 如果遇到一个波谷
            f[i] = f[i - 1]; // 波峰不用更新
            g[i] = max(g[i - 1], f[i - 1] + 1); // 把波谷接在上一次波峰的后面
        }

    cout << max(f[n], g[n]) << endl;
    fflush(stdout);
    return 0;
}
