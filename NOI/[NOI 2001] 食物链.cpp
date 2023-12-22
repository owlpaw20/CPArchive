#include <iostream>
using namespace std;

const int N = 5e4 + 10;

int n, k;
int cnt, p[N], dist[N];

int find_set(int x) {
    if (p[x] == x) return x;
    int t = find_set(p[x]);
    dist[x] += dist[p[x]];
    return p[x] = t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) p[i] = i;

    while (k--) {
        int opt, x, y;
        cin >> opt >> x >> y;

        if (x > n || y > n) {
            cnt++;
            continue;
        }

        int rx = find_set(x);
        int ry = find_set(y);
        int relation = (opt == 1 ? 0 : 1);

        if (rx == ry) {
            if (((dist[x] - dist[y]) % 3 + 3) % 3 != relation)
                cnt++;
        } else {
            p[rx] = ry;
            dist[rx] = dist[y] - dist[x] + relation;
        }
    }

    cout << cnt << endl;

    fflush(stdout);
    return 0;
}
