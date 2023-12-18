#include <iostream>
#include <algorithm>

#define endl '\n'
#define L first
#define R second

using namespace std;
using PII = pair<int, int>;

const int N = 5e4 + 10;

int n;
PII w[N];
int loop[N];
int ans1[N], ans2[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i].L >> w[i].R;

    // 判断是否有矛盾
    for (int i = 1; i <= n; i++) {
        auto [l, r] = w[i];
        if ((w[l].L != i && w[l].R != i) || (w[r].L != i && w[r].R != i))
            return puts("-1"), 0;
    }

    // 构建期望环
    loop[1] = 1;
    loop[2] = w[1].R;
    loop[n] = w[1].L;
    for (int i = 3; i < n; i++)
        if (w[loop[i - 1]].L == loop[i - 2])
            loop[i] = w[loop[i - 1]].R;
        else
            loop[i] = w[loop[i - 1]].L;

    for (int i = 1; i <= n; i++) {
        ans1[(loop[i] - i + n) % n] += 1;
        ans2[(loop[i] + i - 1) % n] += 1;
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max({ans, ans1[i], ans2[i]});

    cout << n - ans << endl;
    fflush(stdout);
    return 0;
}
