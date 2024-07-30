#include <bits/stdc++.h>

int N;
std::deque<int> dq;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N;

  if (N & 1) {
    dq.push_back(1);

    for (int i = 3; i < N; i += 2) {
      for (int j = 1; j < i; ++j)
        if (j & 1) dq.push_back(i), dq.push_back(i - 1);
        else dq.push_front(i - 1), dq.push_front(i);
      dq.push_back(i);
    }

    for (int i = 1; i < N; ++i)
      if (i & 1) dq.push_back(N), dq.push_back(N - 1);
      else dq.push_front(N), dq.push_front(N - 1);

    dq.push_front(N);
  }

  else {
    dq.push_back(2), dq.push_back(1), dq.push_back(2);

    for (int i = 3; i < N - 1; i += 2) {
      for (int j = 1; j <= i; ++j)
        if (j & 1) dq.push_back(i), dq.push_back(i + 1);
        else dq.push_front(i + 1), dq.push_front(i);
      dq.push_front(i + 1);
    }

    for (int i = 1; i < N; ++i)
      if (i & 1) dq.push_back(N), dq.push_back(N - 1);
      else dq.push_front(N), dq.push_front(N - 1);

    dq.push_front(N);
  }

  while (!dq.empty())
    std::cout << dq.front() << ' ', dq.pop_front();

  std::cout.flush();
  return 0;
}
