#include <string>
#include <iostream>

int N;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  bool flag = false;
  for (int i = 1; i <= N; ++i) {
    std::string s;
    std::cin >> s;

    if (s == "sweet" && flag && i != N) return puts("No"), 0;
    else if (s == "sweet") flag = true;
    else flag = false;
  }

  puts("Yes");
  return 0;
}
