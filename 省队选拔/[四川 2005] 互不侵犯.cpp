#include <vector>
#include <iostream>

using namespace std;
using i64 = long long;

const int MAX_ROWS = 11;
const int MAX_STAT = 1 << MAX_ROWS;
const int MAX_KING = MAX_ROWS << 1;

int n, K, kings_cnt[MAX_STAT];
i64 f[MAX_ROWS][MAX_KING][MAX_STAT];
// f[i][j][k] = 前 i 行棋盘放置了 j 个国王且第 i 层状态为 k

vector<int> valid_states;
vector<int> valid_transitions[MAX_STAT];

// 判断当前状态中有没有相邻的国王
bool are_adjacent_kings(int state) { return (state & (state >> 1)); }

// 判断当前状态中国王的数量
int count_kings(int state) {
    int ret = 0;
    for (int i = 0; i < n; i++)
        ret += (state >> i) & 1;
    return ret;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> K;

    // 预处理所有合法的状态
    for (int state = 0; state < (1 << n); state++)
        if (!are_adjacent_kings(state))
            valid_states.push_back(state),
                kings_cnt[state] = count_kings(state);

    // 预处理所有合法的状态转移
    for (int current_state : valid_states)
        for (int next_state : valid_states)
            if (!(current_state & next_state))
                if (!are_adjacent_kings(current_state | next_state))
                    valid_transitions[current_state].push_back(next_state);

    // 动态规划
    f[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= K; j++)
            for (int current_state : valid_states)
                for (int prev_state : valid_transitions[current_state])
                    if (j >= kings_cnt[current_state])  // 如果可以从上一个状态转移过来
                        f[i][j][current_state] += f[i - 1][j - kings_cnt[current_state]][prev_state];

    i64 ans = 0;
    for (int state : valid_states)
        ans += f[n][K][state];

    cout << ans << endl;
    return 0;
}
