#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e4 + 10;

int n, m, ans;
int choice[N];

struct DLX {
    int idx = 0, head[N], sz[N];
    int left[N], right[N], up[N], down[N], row[N], col[N];
    void build(int r, int c) {
        for (int i = 0; i <= c; i++) {
            left[i] = i - 1, right[i] = i + 1;
            up[i] = down[i] = i;
        }
        left[0] = c, right[c] = 0, idx = c;
        memset(head, -1, sizeof head);
        memset(sz, 0, sizeof sz);
    }
    void insert(int r, int c) {
        row[++idx] = r, col[idx] = c, sz[c]++;
        down[idx] = down[c], up[down[c]] = idx;
        up[idx] = c, down[c] = idx;
        if (head[r] == -1)
            head[r] = left[idx] = right[idx] = idx;
        else {
            right[idx] = right[head[r]], left[right[head[r]]] = idx;
            left[idx] = head[r], right[head[r]] = idx;
        }
    }
    void remove(int c) {
        left[right[c]] = left[c], right[left[c]] = right[c];
        for (int i = down[c]; i != c; i = down[i])
            for (int j = right[i]; j != i; j = right[j])
                up[down[j]] = up[j], down[up[j]] = down[j], sz[col[j]]--;
    }
    void restore(int c) {
        for (int i = up[c]; i != c; i = up[i])
            for (int j = left[i]; j != i; j = left[j])
                up[down[j]] = down[up[j]] = j, sz[col[j]]++;
        left[right[c]] = right[left[c]] = c;
    }
    bool process(int depth) {
        if (!right[0]) {
            ans = depth;
            return 1;
        }
        int c = right[0];
        for (int i = right[0]; i != 0; i = right[i])
            if (sz[i] < sz[c])
                c = i;
        remove(c);
        for (int i = down[c]; i != c; i = down[i]) {
            choice[depth] = row[i];
            for (int j = right[i]; j != i; j = right[j]) remove(col[j]);
            if (process(depth + 1)) return 1;
            for (int j = left[i]; j != i; j = left[j]) restore(col[j]);
        }
        restore(c);
        return 0;
    }
} dlx;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    dlx.build(n, m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            bool t;
            cin >> t;
            if (t) dlx.insert(i, j);
        }
    dlx.process(1);
    if (!ans)
        puts("No Solution!");
    else {
        for (int i = 1; i < ans; i++)
            cout << choice[i] << " ";
        cout << endl;
    }
    return 0;
}
