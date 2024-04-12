#include <cstring>
#include <iostream>

using namespace std;

const int N = 3e5 + 10;

int grid[9][9];
int choice[N];

struct DancingLinks {
    int idx = 0, head[N], sz[N];
    int L[N], R[N], U[N], D[N], row[N], col[N];
    void build(int c) {
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
    void restore(int c) {
        for (int i = U[c]; i != c; i = U[i])
            for (int j = L[i]; j != i; j = L[j])
                U[D[j]] = D[U[j]] = j, sz[col[j]]++;
        L[R[c]] = R[L[c]] = c;
    }
    bool process(int depth) {
        if (!R[0]) {
            for (int i = 0; i < depth; i++) {
                int x = (choice[i] - 1) / 81;
                int y = (choice[i] - 1) / 9 % 9;
                int z = choice[i] % 9;
                if (z == 0) z = 9;
                grid[x][y] = z;
            }
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
            for (int j = L[i]; j != i; j = L[j]) restore(col[j]);
        }
        restore(c);
        return 0;
    }
} DLX;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (1) {
        DLX.build(324);
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                char ch;
                cin >> ch;
                if (ch == 'e')
                    exit(0);
                else if (ch == '.')
                    grid[i][j] = 0;
                else
                    grid[i][j] = (int)ch - '0';
                for (int k = 1; k <= 9; k++) {
                    if (grid[i][j] != k && grid[i][j] != 0) continue;
                    int t = i * 81 + j * 9 + k;
                    DLX.insert(t, i * 9 + j + 1);
                    DLX.insert(t, i * 9 + 81 + k);
                    DLX.insert(t, j * 9 + 162 + k);
                    DLX.insert(t, 243 + (i / 3 * 3 + j / 3) * 9 + k);
                }
            }
        DLX.process(0);
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                cout << grid[i][j];
        cout << endl;
    }

    return 0;
}
