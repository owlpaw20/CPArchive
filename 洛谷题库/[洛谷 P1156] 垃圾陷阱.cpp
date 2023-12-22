#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 100 + 5;
const int M = 1000 + 5;
const int INF = 0x3f3f3f3f;

struct Waste {
    int t, f, h;
    bool operator<(const Waste& o) const { return t < o.t; }
};

// f[i][j] 表示处理完前 i 个垃圾后还剩余 j 生命时垃圾的最大高度
int d, n, f[N][M];
bool check[N][M];
Waste a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> d >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i].t >> a[i].f >> a[i].h;
    sort(a + 1, a + n + 1);

    int HP = 10, maxlife = 10;
    for (int i = 1; i <= n; i++) {
        HP -= a[i].t - a[i - 1].t;
        if (HP < 0) break;
        HP += a[i].f;
        maxlife += a[i].f;
    }

    check[0][10] = true;
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = maxlife; j >= 0; j--) {
            // check 数组用于判断当前状态是否有出现的可能
            if (check[i - 1][j + a[i].t - a[i - 1].t]) {
                f[i][j] = max(f[i][j], f[i - 1][j + a[i].t - a[i - 1].t] + a[i].h);           // 用于堆放
                f[i][j + a[i].f] = max(f[i][j + a[i].f], f[i - 1][j + a[i].t - a[i - 1].t]);  // 用于维生
                check[i][j] = check[i][j + a[i].f] = true;
            }

            // 判断是否逃生成功
            if (f[i][j] >= d) {
                ans = a[i].t;
                break;
            }
        }
        if (ans != INF) break;
    }

    cout << (ans == INF ? maxlife : ans) << endl;
    fflush(stdout);
    return 0;
}
