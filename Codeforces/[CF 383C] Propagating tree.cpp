#pragma GCC optimize("O2,unroll-loops")

#include <cstdint>
#include <cstring>
#include <iostream>

#define endl '\n'

using cbool = const bool;
using c32 = const int;
using PII = std::pair<int, int>;

const int MAX_N = 2e5 + 5;
const int MAX_M = 4e5 + 5;

int N, M;
int a[MAX_N], b[MAX_N];

int ed[MAX_M], nx[MAX_M], head[MAX_N], idx;
int depth[MAX_N], timestamp;
PII dfn[MAX_N];

void DFS(c32 u, c32 fa = 0) {
    depth[u] = depth[fa] + 1;
    dfn[u].first = ++timestamp;
    b[timestamp] = u;

    for (int i = head[u]; ~i; i = nx[i])
        if (ed[i] != fa)
            DFS(ed[i], u);

    dfn[u].second = timestamp;
}

struct SEGTREE {
    struct NODE {
        int k, val, tag;

        void push(NODE &lc, NODE &rc) {
            lc.val += tag * lc.k;
            rc.val += tag * rc.k;
            lc.tag += tag;
            rc.tag += tag;
            tag = 0;
        }
    } node[MAX_N << 2];

    void build(c32 u = 1, c32 l = 1, c32 r = N) {
        node[u].k = 0;
        node[u].tag = 0;

        if (l == r) {
            node[u].k = (depth[b[l]] & 1) ? 1 : -1;  // 当前节点深度的奇偶性
            node[u].val = a[b[l]];
            return;
        }

        c32 mid = (l + r) >> 1;

        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
    }

    void update(c32 l, c32 r, c32 x, c32 u = 1, c32 nl = 1, c32 nr = N) {
        if (nl >= l && nr <= r) {
            node[u].val += x * node[u].k;
            node[u].tag += x;
            return;
        }

        if (node[u].tag) node[u].push(node[u << 1], node[u << 1 | 1]);

        c32 mid = (nl + nr) >> 1;

        if (l <= mid) update(l, r, x, u << 1, nl, mid);
        if (r > mid) update(l, r, x, u << 1 | 1, mid + 1, nr);
    }

    int query(c32 x, c32 u = 1, c32 nl = 1, c32 nr = N) {
        if (nl == nr)
            return node[u].val;

        if (node[u].tag) node[u].push(node[u << 1], node[u << 1 | 1]);

        c32 mid = (nl + nr) >> 1;

        if (x <= mid) return query(x, u << 1, nl, mid);
        return query(x, u << 1 | 1, mid + 1, nr);
    }
} SGT;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    memset(head, -1, sizeof head);

    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i) std::cin >> a[i];

    auto connect = [&](c32 u, c32 v) -> void {
        ed[idx] = v;
        nx[idx] = head[u];
        head[u] = idx++;
    };

    for (int i = 1, u, v; i < N; ++i) {
        std::cin >> u >> v;
        connect(u, v);
        connect(v, u);
    }

    DFS(1);
    SGT.build();

    while (M--) {
        int type, u, val;
        std::cin >> type >> u;

        if (type == 1) {
            std::cin >> val;
            SGT.update(dfn[u].first, dfn[u].second, ((depth[u] & 1) ? val : -val));
        } else
            std::cout << SGT.query(dfn[u].first) << endl;
    }

    return fflush(stdout), 0;
}
