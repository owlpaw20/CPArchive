#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;
using std::vector;

using PII = std::pair<int, int>;

const int MAX_N = 5e5 + 5;

int N, M;
PII seg[MAX_N];
vector<int> disc;

struct SegTree {
    struct Node {
        int l, r;
        int tag, max;
    } node[MAX_N << 3];

    void pushup(int u) {
        node[u].max = std::max(node[u << 1].max, node[u << 1 | 1].max);
    }

    void pushdown(int u) {
        if (node[u].tag) {
            node[u << 1].tag += node[u].tag;
            node[u << 1].max += node[u].tag;
            node[u << 1 | 1].tag += node[u].tag;
            node[u << 1 | 1].max += node[u].tag;
            node[u].tag = 0;
        }
    }

    void build(int l, int r, int u = 1) {
        node[u] = {l, r, 0, 0};

        if (l == r) return;

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
    }

    void update(int l, int r, int x = 1, int u = 1) {
        if (node[u].l >= l && node[u].r <= r) {
            node[u].tag += x;
            node[u].max += x;
            return;
        }

        pushdown(u);

        int mid = (node[u].l + node[u].r) >> 1;

        if (l <= mid) update(l, r, x, u << 1);
        if (r > mid) update(l, r, x, u << 1 | 1);

        pushup(u);
    }
} SGT;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> seg[i].first >> seg[i].second;
        disc.push_back(seg[i].first);
        disc.push_back(seg[i].second);
    }

    auto cmp = [&](PII x, PII y) {
        return x.second - x.first < y.second - y.first;
    };
    std::sort(seg + 1, seg + N + 1, cmp);
    std::sort(disc.begin(), disc.end());
    disc.erase(std::unique(disc.begin(), disc.end()), disc.end());

    for (int i = 1; i <= N; i++) {
        seg[i].first = std::lower_bound(disc.begin(), disc.end(), seg[i].first) - disc.begin() + 1;
        seg[i].second = std::lower_bound(disc.begin(), disc.end(), seg[i].second) - disc.begin() + 1;
    }

    SGT.build(1, disc.size());

    int ans = std::numeric_limits<int>::max();
    auto len = [&](int x) {
        return disc[seg[x].second - 1] - disc[seg[x].first - 1];
    };

    for (int i = 1, l = 1; i <= N; i++) {
        SGT.update(seg[i].first, seg[i].second);
        while (SGT.node[1].max >= M) {
            ans = std::min(ans, len(i) - len(l));
            SGT.update(seg[l].first, seg[l].second, -1);
            l++;
        }
    }

    if (ans == std::numeric_limits<int>::max()) ans = -1;
    cout << ans << endl;
    return fflush(stdout), 0;
}
