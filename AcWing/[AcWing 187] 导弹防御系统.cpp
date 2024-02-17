#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 60;

int n;
int a[N], ans;
int fUp[N], fDown[N];

void DFS(int up, int down, int i) {
    if (up + down >= ans)  // 最优性剪枝
        return;

    if (i > n) {                    // 如果已经遍历完了所有点
        ans = min(ans, up + down);  // 则求最优解
        return;                     // 并退出搜索
    }

    int j;
    for (j = 1; j <= up; j++)  // 在所有上升子序列中
        if (fUp[j] < a[i])     // 找到第一个末尾数小于 a[i] 的系统
            break;             // 如果在已有子序列中找不到，则 j = up + 1

    int tmp = fUp[j];
    fUp[j] = a[i];                 // 更新 DP 数组对应位置的值
    DFS(max(up, j), down, i + 1);  // 递归地进行 DP
    fUp[j] = tmp;                  // 回溯

    int k;
    for (k = 1; k <= down; k++)  // 在所有下降子序列中
        if (fDown[k] > a[i])     // 找到第一个末尾数大于 a[i] 的系统
            break;               // 如果在已有子序列中找不到，则 k = down + 1

    int ttmp = fDown[k];
    fDown[k] = a[i];               // 更新 DP 数组对应位置的值
    DFS(up, max(down, k), i + 1);  // 递归地进行 DP
    fDown[k] = ttmp;               // 回溯
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n, n) {
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        ans = 50;
        DFS(0, 0, 1);  // 从无上升系统、无下降系统、第 i 发导弹的情况开始 DP

        cout << ans << endl;
    }

    fflush(stdout);
    return 0;
}
