#include <bits/stdc++.h>

const int MAX_N = 100'005;

int N, M;
long long ans[MAX_N];

struct Event {
  int t, s, f, id;
  auto operator<=>(const Event& rhs) const = default;
} e[MAX_N];

std::vector<std::vector<int>> wait;
std::vector<std::vector<int>> dest;

std::priority_queue<int> d, wd;
std::priority_queue<int, std::vector<int>, std::greater<int>> u, wu;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  wait.resize(M + 1), dest.resize(M + 1);

  for (int i = 1, t, s, f; i <= N; ++i) {
    std::cin >> t >> s >> f;
    e[i] = {t, s, f, i};
  }

  std::sort(e + 1, e + N + 1);

  int i = 1, pos = 1;
  long long t = 0;

  auto empty = [&]() { return d.empty() && wd.empty() && u.empty() && wu.empty(); };
  auto check = [&]() { return u.size() + wu.size() >= d.size() + wd.size(); };

  auto get_closest = [&](bool flag) {
    if (flag) {
      if (u.empty() || wu.empty()) return u.empty() ? wu.top() : u.top();
      return std::min(u.top(), wu.top());
    }

    if (d.empty() || wd.empty()) return d.empty() ? wd.top() : d.top();
    return std::max(d.top(), wd.top());
  };

  auto direct = [&]() {
    dest[e[i].f].push_back(i);
    e[i].f > pos ? u.push(e[i].f) : d.push(e[i].f);
  };

  auto queue = [&]() {
    wait[e[i].s].push_back(i);
    e[i].s > pos ? wu.push(e[i].s) : wd.push(e[i].s);
  };

  auto offboard = [&](bool flag) {
    int i = dest[pos].back();
    dest[pos].pop_back();
    flag ? u.pop() : d.pop();
    ans[e[i].id] = t;
  };

  auto onboard = [&](bool flag) {
    int i = wait[pos].back();
    wait[pos].pop_back();
    dest[e[i].f].push_back(i);
    flag ? wu.pop() : wd.pop();
    e[i].f > pos ? u.push(e[i].f) : d.push(e[i].f);
  };

  while (i <= N) {
    t = e[i].t;
    (e[i].s == pos ? direct() : queue()), ++i;

    while (!empty()) {
      while (i <= N && e[i].t == t) (e[i].s == pos ? direct() : queue()), ++i;

      bool flag = check();
      int closest = get_closest(flag);

      if (i > N || abs(closest - pos) <= e[i].t - t) {
        t += abs(closest - pos), pos = closest;
        int off = dest[pos].size(), on = wait[pos].size();
        while (off--) offboard(flag);
        while (on--) onboard(flag);
      }

      else {
        int dist = e[i].t - t;
        flag ? pos += dist : pos -= dist;
        t = e[i].t;
      }
    }
  }

  for (int i = 1; i <= N; ++i) std::cout << ans[i] << '\n';
  return 0;
}
