#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 1e4 + 10;

int n, m, ans;
int choice[N];

struct DLX {
    int idx = 0, head[N], sz[N];
    int L[N], R[N], U[N], D[N], row[N], col[N];
    void build(int r, int c) {
        for (int i = 0; i <= c; i++) {
            L[i] = i - 1, R[i] = i + 1;
            U[i] = D[i] = i;
        }
        L[0] = c, R[c] = 0, idx = c;
        memset(head, -1, sizeof head);
        memset(sz, 0, sizeof sz);
    }
    void insert(int r, int c) {
        row[++idx] = r, col[idx] = c, sz[c]++;
        D[idx] = D[c], U[D[c]] = idx;
        U[idx] = c, D[c] = idx;
        if (head[r] == -1)
            head[r] = L[idx] = R[idx] = idx;
        else {
            R[idx] = R[head[r]], L[R[head[r]]] = idx;
            L[idx] = head[r], R[head[r]] = idx;
        }
    }
    void remove(int c) {
        L[R[c]] = L[c], R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i])
            for (int j = R[i]; j != i; j = R[j])
                U[D[j]] = U[j], D[U[j]] = D[j], sz[col[j]]--;
    }
    void recover(int c) {
        for (int i = U[c]; i != c; i = U[i])
            for (int j = L[i]; j != i; j = L[j])
                U[D[j]] = D[U[j]] = j, sz[col[j]]++;
        L[R[c]] = R[L[c]] = c;
    }
    bool process(int depth) {
        if (!R[0]) {
            ans = depth;
            return 1;
        }
        int c = R[0];
        for (int i = R[0]; i != 0; i = R[i])
            if (sz[i] < sz[c])
                c = i;
        remove(c);
        for (int i = D[c]; i != c; i = D[i]) {
            choice[depth] = row[i];
            for (int j = R[i]; j != i; j = R[j]) remove(col[j]);
            if (process(depth + 1)) return 1;
            for (int j = L[i]; j != i; j = L[j]) recover(col[j]);
        }
        recover(c);
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
