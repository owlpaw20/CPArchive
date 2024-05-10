#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>

using l64 = long long;

const int MAX_N = 1e5 + 5;
const l64 INF = 1e18;

int N;
l64 a[MAX_N], ans;

struct MyHash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

std::unordered_map<l64, l64, MyHash> bucket;

void solve() {
  std::cin >> N;
  ans = 0;

  bucket.clear();
  bucket[0] = 1;

  char ch;
  for (int i = 1; i <= N; ++i) {
    std::cin >> ch;
    a[i] = a[i - 1] + ch - '0';
    ans += bucket[a[i] - i]++;
  }

  std::cout << ans << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) solve();

  return fflush(stdout), 0;
}
