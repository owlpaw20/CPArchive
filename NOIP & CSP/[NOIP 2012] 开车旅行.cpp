#include <set>
#include <cmath>
#include <iostream>

#define endl '\n'

using f64 = double;
using i64 = long long;
using PII = std::pair<i64, int>;

const int MAX_N = 1e5 + 5;
const i64 INF = 1e16;
const f64 EPS = 1e-15;

int N;
i64 h[MAX_N];
int x_0, M, c[MAX_N], x[MAX_N];

int f[MAX_N][18][2];  // 从城市 I 出发，行驶 (1 << J) 天，K 先开车，最终会到达的城市编号
int a[MAX_N][18][2];  // 从城市 I 出发，行驶 (1 << J) 天，K 先开车，小 A 行驶的路程长度
int b[MAX_N][18][2];  // 从城市 I 出发，行驶 (1 << J) 天，K 先开车，小 B 行驶的路程长度

// 通过平衡树来维护以高度为排序关键字，每个城市的前驱与后继
// 由于 INF 范围问题，需要使用 long long 存储，如果 set 放在函数内将会爆内存
std::set<PII> set;

// 预处理小 A 和小 B 从每一个城市出发到达的下一个城市
void prep() {
    // 迭代器越界保护
    set.emplace(INF, 0);
    set.emplace(-INF, N + 1);

    for (int i = N; i; --i) {  // 倒序插入，保证 set 内只有未来的城市
        set.emplace(h[i], i);

        std::set<PII>::const_iterator k = set.lower_bound(PII(h[i], i));
        std::set<PII>::iterator pre = k, nxt = k;

        auto [pre_h, pre_id] = *(--pre);  // 获取前驱
        auto [nxt_h, nxt_id] = *(++nxt);  // 获取后继

        int opt_a, opt_b;

        if (fabsl(nxt_h - h[i]) >= fabsl(h[i] - pre_h)) {                              // 如果后继比前驱近
            opt_b = pre_id;                                                            // 则小 B 将会前往的下一个城市是后继
            auto [ppre_h, ppre_id] = *(--pre);                                         // 同时获取后继的后继
            opt_a = (fabsl(nxt_h - h[i]) >= fabsl(h[i] - ppre_h)) ? ppre_id : nxt_id;  // 判断小 A 将会前往的城市
        } else {
            opt_b = nxt_id;  // 同理
            auto [nnxt_h, nnxt_id] = *(++nxt);
            opt_a = (fabsl(nnxt_h - h[i]) >= fabsl(h[i] - pre_h)) ? pre_id : nnxt_id;
        }

        // 初始情况下，从城市 I 出发，行驶一天所到达的城市
        f[i][0][0] = opt_a, f[i][0][1] = opt_b;

        // 小 A 和小 B 的第一天行驶路程
        a[i][0][0] = fabsl(h[i] - h[opt_a]);
        b[i][0][1] = fabsl(h[i] - h[opt_b]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;
    for (int i = 1; i <= N; ++i) std::cin >> h[i];

    std::cin >> x_0 >> M;
    for (int i = 1; i <= M; ++i) std::cin >> c[i] >> x[i];

    prep();

    // 倍增更新行驶若干天之后的动态规划数组
    for (int j = 1; j <= 17; ++j)
        for (int i = 1; i <= N; ++i)
            for (int k = 0; k < 2; ++k) {
                // 当 j == 1 时，前一天 j = 0，只行驶了奇数天，所以需要从另一个人的状态转移过来
                f[i][j][k] = f[f[i][j - 1][k]][j - 1][k ^ (j == 1)];
                a[i][j][k] = a[i][j - 1][k] + a[f[i][j - 1][k]][j - 1][k ^ (j == 1)];
                b[i][j][k] = b[i][j - 1][k] + b[f[i][j - 1][k]][j - 1][k ^ (j == 1)];
            }

    // 从城市 p 出发，最多行驶 x 公里，则小 A 和小 B 最多行驶了多少距离
    auto calc = [&](int p, const int x) -> PII {
        int len_a = 0, len_b = 0;
        for (int i = 17; ~i; --i)
            if (f[p][i][0] && len_a + len_b + a[p][i][0] + b[p][i][0] <= x) {
                len_a += a[p][i][0];
                len_b += b[p][i][0];
                p = f[p][i][0];
            }
        return PII(len_a, len_b);
    };

    int ans_id = 0;
    f64 ans_ratio = INF;
    auto fcmp = [](const f64 x, const f64 y) -> int {
        if (fabsl(x - y) <= EPS) return 0;
        return (x - y > 0) ? 1 : -1;
    };

    // 第一问，求解比值最小的城市
    for (int i = 1; i <= N; ++i) {
        auto [len_a, len_b] = calc(i, x_0);
        f64 ratio = (len_b) ? (len_a * 1.0 / len_b) : INF;

        if (fcmp(ratio, ans_ratio) == -1) {
            ans_id = i;
            ans_ratio = ratio;
        } else if (!fcmp(ratio, ans_ratio) && fcmp(h[ans_id], h[i]) == -1)
            ans_id = i;
    }

    std::cout << ans_id << endl;

    // 第二问，求解两者的行驶距离
    for (int i = 1; i <= M; ++i) {
        auto [len_a, len_b] = calc(c[i], x[i]);
        std::cout << len_a << ' ' << len_b << endl;
    }

    return fflush(stdout), 0;
}
