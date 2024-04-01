#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 25;

struct Point {
    int x, y, num;
    Point(int a, int b, int c) : x(a), y(b), num(c) {}
    bool operator<(const Point& t) const {
        return num > t.num;
    }
};

int m, n, k;
vector<Point> p;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            int t;
            cin >> t;
            if (t != 0) p.emplace_back(i, j, t);
        }

    sort(p.begin(), p.end());

    if (p[0].x * 2 + 1 > k) return puts("0") && 0;

    int ans = p[0].num;
    k -= p[0].x + 1;
    for (int i = 1; i < p.size(); i++) {
        int d = abs(p[i - 1].x - p[i].x) + abs(p[i - 1].y - p[i].y);
        if (d + p[i].x + 1 > k) break;
        ans += p[i].num;
        k -= d + 1;
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
