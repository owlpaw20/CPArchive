#include <string>
#include <numeric>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;

const int N = 4e4 + 5;
const int M = 2e4;

int n, m;
int fa[N];

int idx;
unordered_map<int, int> disc;

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

int H(int x) {
    if (disc.count(x)) return disc[x];
    return disc[x] = ++idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    iota(fa, fa + N - 10, 0);

    for (int i = 1, l, r; i <= m; i++) {
        string type;
        cin >> l >> r >> type;
        l = H(l - 1), r = H(r);

        if (type == "even") {
            if (find(l + M) == find(r) || find(r + M) == find(l)) {
                cout << i - 1 << endl;
                exit(0);
            }
            fa[find(l)] = find(r);
            fa[find(l + M)] = find(r + M);
        } else {
            if (find(l) == find(r) || find(l + M) == find(r + M)) {
                cout << i - 1 << endl;
                exit(0);
            }
            fa[find(l + M)] = find(r);
            fa[find(l)] = find(r + M);
        }
    }

    cout << m << endl;
    fflush(stdout);
    return 0;
}
