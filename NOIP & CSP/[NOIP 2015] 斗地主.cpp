#include <climits>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 20;

int n, ans;
int remain[N];  // 统计每种点数的牌有多少张

void DFS(int index, int step, int discarded) {
    if (step >= ans)  // 最优性剪枝
        return;

    if (discarded >= n)                       // 如果已经发完所有的牌
        return (void)(ans = min(ans, step));  // 则统计答案

    if (index > 15)  // 已经发完所有点数的牌
        return;

    if (remain[index] == 0)                      // 如果当前点数已经无牌可用
        return DFS(index + 1, step, discarded);  // 则直接进行下一个点数的搜索

    // 如果有王炸可用
    if (remain[14] != 0 && remain[15] != 0) {
        remain[14]--, remain[15]--;
        DFS(index, step + 1, discarded + 2);
        remain[14]++, remain[15]++;
    }

    // 如果有四张相同点数的牌可用
    if (remain[index] >= 4) {
        remain[index] -= 4;

        // 单走一个炸弹
        DFS(index, step + 1, discarded + 4);

        // 四带两单牌
        for (int i = 1; i <= 15; i++)
            if (remain[i] >= 1) {
                remain[i]--;
                for (int j = 1; j <= 15; j++)
                    if (remain[j] >= 1) {
                        remain[j]--;
                        DFS(index, step + 1, discarded + 6);
                        remain[j]++;
                    }
                remain[i]++;
            }

        // 四带两对子
        for (int i = 1; i <= 13; i++)
            if (remain[i] >= 2) {
                remain[i] -= 2;
                for (int j = 1; j <= 13; j++)
                    if (remain[j] >= 2) {
                        remain[j] -= 2;
                        DFS(index, step + 1, discarded + 8);
                        remain[j] += 2;
                    }
                remain[i] += 2;
            }

        remain[index] += 4;
    }

    if (remain[index] >= 3) {
        remain[index] -= 3;

        // 单走一个三张牌
        DFS(index, step + 1, discarded + 3);

        // 三带一
        for (int i = 1; i <= 15; i++) {
            if (i == index) continue;
            if (remain[i] >= 1) {
                remain[i]--;
                DFS(index, step + 1, discarded + 4);
                remain[i]++;
            }
        }

        // 三带二
        for (int i = 1; i <= 13; i++) {
            if (i == index) continue;
            if (remain[i] >= 2) {
                remain[i] -= 2;
                DFS(index, step + 1, discarded + 5);
                remain[i] += 2;
            }
        }

        // 三顺子
        for (int i = index + 1; i <= 12; i++) {
            if (remain[i] < 3) break;  // 顺子中断
            if (i - index + 1 >= 2) {  // 三顺子只需要两种连续点数即可
                for (int j = index + 1; j <= i; j++) remain[j] -= 3;
                DFS(index, step + 1, discarded + (i - index + 1) * 3);
                for (int j = index + 1; j <= i; j++) remain[j] += 3;
            }
        }

        remain[index] += 3;
    }

    if (remain[index] >= 2) {
        remain[index] -= 2;

        // 单走一个对子
        DFS(index, step + 1, discarded + 2);

        // 二带三
        for (int i = 1; i <= 13; i++) {
            if (i == index) continue;
            if (remain[i] >= 3) {
                remain[i] -= 3;
                DFS(index, step + 1, discarded + 5);
                remain[i] += 3;
            }
        }

        // 对子带四带对子
        for (int i = 1; i <= 13; i++) {
            if (i == index) continue;
            if (remain[i] >= 4) {
                remain[i] -= 4;
                for (int j = 1; j <= 13; j++) {
                    if (j == i) continue;
                    if (remain[j] >= 2) {
                        remain[j] -= 2;
                        DFS(index, step + 1, discarded + 8);
                        remain[j] += 2;
                    }
                }
                remain[i] += 4;
            }
        }

        // 双顺子
        for (int i = index + 1; i <= 12; i++) {
            if (remain[i] < 2) break;  // 顺子中断
            if (i - index + 1 >= 3) {  // 双顺子需要三种连续点数
                for (int j = index + 1; j <= i; j++) remain[j] -= 2;
                DFS(index, step + 1, discarded + (i - index + 1) * 2);
                for (int j = index + 1; j <= i; j++) remain[j] += 2;
            }
        }

        remain[index] += 2;
    }

    if (remain[index] >= 1) {
        remain[index]--;

        // 单走一个六
        DFS(index, step + 1, discarded + 1);

        // 一带三
        for (int i = 1; i <= 13; i++) {
            if (i == index) continue;
            if (remain[i] >= 3) {
                remain[i] -= 3;
                DFS(index, step + 1, discarded + 4);
                remain[i] += 3;
            }
        }

        // 单牌带四带单牌
        for (int i = 1; i <= 13; i++) {
            if (i == index) continue;
            if (remain[i] >= 4) {
                remain[i] -= 4;
                for (int j = 1; j <= 15; j++) {
                    if (j == i) continue;
                    if (remain[j] >= 1) {
                        remain[j]--;
                        DFS(index, step + 1, discarded + 6);
                        remain[j]++;
                    }
                }
                remain[i] += 4;
            }
        }

        // 单顺子
        for (int i = index + 1; i <= 12; i++) {
            if (remain[i] < 1) break;  // 顺子中断
            if (i - index + 1 >= 5) {  // 单顺子需要五种连续点数
                for (int j = index + 1; j <= i; j++) remain[j]--;
                DFS(index, step + 1, discarded + (i - index + 1));
                for (int j = index + 1; j <= i; j++) remain[j]++;
            }
        }

        remain[index]++;
    }
}

void solve() {
    ans = INT_MAX;
    memset(remain, 0, sizeof remain);

    // 初始牌型输入
    for (int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        if (a == 1)
            remain[12]++;
        else if (a == 2)
            remain[13]++;
        else if (a == 0 && b == 1)
            remain[14]++;
        else if (a == 0 && b == 2)
            remain[15]++;
        else
            remain[a - 2]++;
    }

    DFS(1, 0, 0);

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T >> n;
    while (T--) solve();

    fflush(stdout);
    return 0;
}
