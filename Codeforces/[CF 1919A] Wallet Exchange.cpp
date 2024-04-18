#include <iostream>

#define endl '\n'

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int a, b;
    cin >> a >> b;

    int sum = a + b;
    if (sum & 1)
      puts("Alice");
    else
      puts("Bob");
  }

  fflush(stdout);
  return 0;
}
