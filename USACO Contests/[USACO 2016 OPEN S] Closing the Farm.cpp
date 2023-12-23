#include <vector>
#include <iostream>
using namespace std;
using PII = pair<int, int>;

struct DisjointSet {
    vector<int> p;
    void init(int n) {
        p.resize(n + 5);
        for (int i = 1; i <= n; i++)
            p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        p[rx] = ry;
        return true;
    }
    DisjointSet(){};
    DisjointSet(int n) { init(n); }
};

const int N = 3e3 + 10;

int n, m, ord[N];
PII shut[N];
bool flag[N];
DisjointSet dsu;
vector<int> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    dsu.init(n);
    for (int i = 1; i <= m; i++)
        cin >> shut[i].first >> shut[i].second;
    for (int i = 1; i <= n; i++) {
        cin >> ord[i];
        flag[ord[i]] = true;
    }

    for (int i = n; i > 0; i--) {
        flag[ord[i]] = false;
        for (int j = 1; j <= m; j++) {
            auto [u, v] = shut[j];
            if (flag[u] == 0 && flag[v] == 0)
                dsu.merge(u, v);
        }
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (dsu.find(j) == j && flag[j] == 0)
                cnt += 1;
        ans.push_back(cnt);
    }

    for (auto it = ans.rbegin(); it != ans.rend(); it++)
        puts((*it == 1 ? "YES" : "NO"));
    return 0;
}
