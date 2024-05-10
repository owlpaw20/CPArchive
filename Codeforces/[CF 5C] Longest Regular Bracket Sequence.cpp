#pragma GCC optimize("O2,unroll-loops")

#include <stack>
#include <bitset>
#include <string>
#include <vector>
#include <iostream>

const int MAX_N = 1e6 + 5;

std::string s;
std::stack<int, std::vector<int>> stack;
std::bitset<MAX_N> flag;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> s;
  int N = s.length();

  for (int i = 0; i < N; ++i)
    if (s[i] == '(') stack.push(i);
    else if (!stack.empty()) flag.set(stack.top()), flag.set(i), stack.pop();

  int max_len = 0, max_cnt = 0;

  for (int i = 0, len = 0; i <= N; ++i)
    if (flag.test(i)) ++len;
    else {
      if (len > max_len) max_len = len, max_cnt = 1;
      else if (len == max_len) ++max_cnt;
      len = 0;
    }

  if (max_len == 0) std::cout << 0 << ' ' << 1 << '\n';
  else std::cout << max_len << ' ' << max_cnt << '\n';

  return fflush(stdout), 0;
}
