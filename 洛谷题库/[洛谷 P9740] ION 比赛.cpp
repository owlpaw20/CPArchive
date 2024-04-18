#include <vector>
#include <iostream>
using namespace std;

const int N = 10;

struct Problem {
  int cnt, ac, per, wa;
  Problem(int _cnt, int _ac) : cnt(_cnt), ac(_ac), per(100 / _cnt), wa(_cnt - _ac) {}
};

int n, score, t;
vector<Problem> p;

int ceil(int x, int y) {
  if (x % y == 0) return x / y;
  return x / y + 1;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
    score += p.back().ac * p.back().per;
  }
  cin >> t;

  if (score >= t) return 0 & puts("Already Au.");

  int delta = t - score;
  for (Problem prob : p)
    if (prob.wa == 0)
      puts("NaN");
    else if (delta > prob.wa * prob.per)
      puts("NaN");
    else
      printf("%d\n", ceil(delta, prob.per));
  return 0;
}
