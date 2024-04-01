#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

struct SegmentBounds {
    double x, y1, y2;
    int diff;
    bool operator<(const SegmentBounds& t) const {
        return x < t.x;
    }
    SegmentBounds(double _x, double _y1, double _y2, int _diff)
        : x(_x), y1(_y1), y2(_y2), diff(_diff) {}
};

struct SegmentTree {
    struct Node {
        int l, r;
        int sum;
        double len;
    };

    vector<Node> tree;
    vector<double> y_axis;

    void init(int n, vector<double>& arr) {
        y_axis = arr;
        tree.clear();
        tree.resize(n * 8 + 100);
    }

    void maintain(int u) {
        if (tree[u].sum)
            tree[u].len = y_axis[tree[u].r + 1] - y_axis[tree[u].l];
        else if (tree[u].l != tree[u].r)
            tree[u].len = tree[u << 1].len + tree[u << 1 | 1].len;
        else
            tree[u].len = 0;
    }

    void build(int l, int r, int u = 1) {
        if (l == r)
            return (void)(tree[u] = {l, r, 0, 0.0});
        tree[u] = {l, r, 0, 0.0};
        int mid = (l + r) >> 1;
        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);
    }

    void update(int l, int r, int delta, int u = 1) {
        int tl = tree[u].l, tr = tree[u].r;
        if (tl >= l && tr <= r) {
            tree[u].sum += delta;
            maintain(u);
            return;
        }
        int mid = (tl + tr) >> 1;
        if (l <= mid) update(l, r, delta, u << 1);
        if (r > mid) update(l, r, delta, u << 1 | 1);
        maintain(u);
    }
};

int n;
SegmentTree SGT;
vector<double> y_axis;
vector<SegmentBounds> x_axis;

int find(double y) {
    return lower_bound(y_axis.begin(), y_axis.end(), y) - y_axis.begin();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int T = 1;; T++) {
        cin >> n;
        if (n == 0)
            break;

        x_axis.clear();
        y_axis.clear();
        for (int i = 1; i <= n; i++) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x_axis.emplace_back(x1, y1, y2, 1);
            x_axis.emplace_back(x2, y1, y2, -1);
            y_axis.emplace_back(y1);
            y_axis.emplace_back(y2);
        }
        sort(y_axis.begin(), y_axis.end());
        y_axis.erase(unique(y_axis.begin(), y_axis.end()), y_axis.end());

        SGT.init(n, y_axis);
        SGT.build(0, y_axis.size() - 2);

        sort(x_axis.begin(), x_axis.end());

        double ans = 0;
        for (int i = 0; i < n << 1; i++) {
            if (i > 0)
                ans += SGT.tree[1].len * (x_axis[i].x - x_axis[i - 1].x);
            SGT.update(find(x_axis[i].y1), find(x_axis[i].y2) - 1, x_axis[i].diff);
        }

        printf("Test case #%d\n", T);
        printf("Total explored area: %.2lf\n\n", ans);
    }

    fflush(stdout);
    return 0;
}
