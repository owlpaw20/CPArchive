#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 10 + 5;
const int M = 1e2 + 5;
const int P = 6e4 + 5;
const int pb3[] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};

int n, m, ans;
bool b[M][N];
int f[M][P];  // 2 = 当前位置为炮塔，1 = 当前位置在炮塔下方一格处，0 = 其他情况
int prv[N], now[N];

// 三进制转十进制
int to_dec(int* ter) {
    int ret = 0;
    for (int i = 1; i <= m; i++)
        ret += pb3[i - 1] * ter[i];
    return ret;
}

// 十进制转三进制
void to_ter(int x, int* ter) {
    for (int i = 1; i <= m; i++)
        ter[i] = x % 3, x /= 3;
}

// 通过 DFS 进行状态转移
void DFS(int x, int cnt, int cur) {
    int dec_st = to_dec(now);

    f[cur][dec_st] = max(f[cur][dec_st], cnt);
    ans = max(ans, cnt);

    for (int i = x; i <= m; i++) {
        if (prv[i]) continue;     // 上一行必须为 0，否则就会被其他炮塔攻击到
        if (now[i]) continue;     // 这一行必须为 0，否则就会被其他炮塔攻击到
        if (b[cur][i]) continue;  // 当前位置必须没有山地阻挡

        now[i] = 2;                // 标记为炮塔
        DFS(i + 3, cnt + 1, cur);  // 从当前行下一个可能的位置继续递归
        now[i] = 0;                // 回溯
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            if (ch == 'H')
                b[i][j] = true;  // 标记当前位置是否为山地
        }

    memset(f, -1, sizeof f);
    f[0][0] = 0;  // 初始化

    for (int i = 1; i <= n; i++)
        for (int j = 0; j < pb3[m]; j++) {
            if (f[i - 1][j] == -1)  // 如果上一行的这个位置没有更新过
                continue;           // 表明遍历到了 m 在三进制表示下的边界

            to_ter(j, prv);  // 将状态转化为三进制表示
            for (int k = 1; k <= m; k++)
                now[k] = max(0, prv[k] - 1);  // 由上一行的状态更新当前行的状态

            DFS(1, f[i - 1][j], i);  // 转移
        }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
