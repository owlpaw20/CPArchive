#include <cmath>
#include <iostream>

#define endl '\n'

using namespace std;

int sx, sy;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> sx >> sy;

  double sum = 0;

  double ax, ay, bx, by;
  while (cin >> ax >> ay >> bx >> by)
    sum += sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));

  double time = sum * 2 / 20000;
  int hr = time;
  int mi = round((time - hr) * 60);

  printf("%d:%02d\n", hr, mi);
  fflush(stdout);
  return 0;
}
