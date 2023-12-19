#include <iostream>

#define endl '\n'

using namespace std;

const int N = 6e5 + 10;
const int M = N * 25;

int n, m;
int p[N];

struct PrstTrie {
    int root[N];
    int trie[M][2];
    int latest[M];
    int idx;

    // 可持久化字典树插入
    void insert(int i) {
        int f = root[i];
        int last_f = 0;
        if (i) last_f = root[i - 1];

        for (int j = 23; j >= 0; j--) {
            int c = p[i] >> j & 1;
            trie[f][c] = ++idx;
            if (last_f) {
                trie[f][c ^ 1] = trie[last_f][c ^ 1];
                last_f = trie[last_f][c];
            }
            latest[idx] = i;
            f = trie[f][c];
        }

        latest[f] = i;
    }

    // 可持久化字典树查询
    int query(int l, int r, int x) {
        int f = root[r];

        for (int i = 23; i >= 0; i--) {
            int c = x >> i & 1;
            if (latest[trie[f][c ^ 1]] >= l) f = trie[f][c ^ 1];
            else f = trie[f][c];
        }

        return x ^ p[latest[f]];
    }

    PrstTrie() {
        idx = 0;
        latest[0] = -1;
        root[0] = ++idx;
        insert(0);
    }
} trie;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        p[i] = p[i - 1] ^ x;
        trie.root[i] = ++trie.idx;
        trie.insert(i);
    }

    int l, r, x;
    char opt;
    while (m--) {
        cin >> opt;
        if (opt == 'A') {
            cin >> x;
            n++, p[n] = p[n - 1] ^ x;
            trie.root[n] = ++trie.idx;
            trie.insert(n);
        } else {
            cin >> l >> r >> x;
            cout << trie.query(l - 1, r - 1, p[n] ^ x) << endl;
        }
    }

    fflush(stdout);
    return 0;
}
