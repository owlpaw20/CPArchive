#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 4e4 + 40;
const int M = 1e5 + 10;

int n, m, p[N], ans;

struct node {
    int a, b, ifl;
} h[M];

int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}

void merge(int x, int y) {
    p[find(x)] = find(y);
    return;
}

bool cmp(node a, node b) {
    return a.ifl > b.ifl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= 2 * n; i++) p[i] = i;
    for (int i = 1; i <= m; i++)
        cin >> h[i].a >> h[i].b >> h[i].ifl;

    sort(h + 1, h + m + 1, cmp);

    for (int i = 1; i <= m; i++) {
        if (find(h[i].a) == find(h[i].b)) {
            ans = h[i].ifl;
            break;
        }
        merge(h[i].a + n, h[i].b);
        merge(h[i].a, h[i].b + n);
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
