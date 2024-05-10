#pragma GCC optimize("O2,unroll-loops,inline")

#include <string>
#include <iostream>

using PII = std::pair<int, int>;

const int MAX_N = 1e6 + 5;

int N;
std::string s;

struct SegT {
  PII cnt[MAX_N << 2], ret;

  // first = 当前区间内未匹配的左括号数量
  // second = 当前区间内未匹配的右括号数量

  PII merge(PII lc, PII rc) {  // 未匹配括号的总数减去合并后成功匹配的对数
    ret.first = lc.first + rc.first - std::min(lc.first, rc.second);
    ret.second = lc.second + rc.second - std::min(lc.first, rc.second);
    return ret;
  }

  void build(int u = 1, int nl = 1, int nr = N) {
    if (nl == nr) return s[nl - 1] == '(' ? cnt[u].first = 1 : cnt[u].second = 1, void();
    int mid = (nl + nr) >> 1;
    build(u << 1, nl, mid);
    build(u << 1 | 1, mid + 1, nr);
    cnt[u] = merge(cnt[u << 1], cnt[u << 1 | 1]);
  }

  PII query(int l, int r, int u = 1, int nl = 1, int nr = N) {
    if (nl >= l && nr <= r) return cnt[u];
    int mid = (nl + nr) >> 1;
    if (l > mid) return query(l, r, u << 1 | 1, mid + 1, nr);
    if (r <= mid) return query(l, r, u << 1, nl, mid);
    return merge(query(l, r, u << 1, nl, mid), query(l, r, u << 1 | 1, mid + 1, nr));
  }
} SEGT;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> s;
  N = s.length();

  SEGT.build();

  int M;
  std::cin >> M;
  while (M--) {
    int l, r;
    std::cin >> l >> r;

    PII ret = SEGT.query(l, r);
    std::cout << (r - l + 1) - ret.first - ret.second << '\n';
  }

  return fflush(stdout), 0;
}
