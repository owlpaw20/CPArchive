#pragma GCC optimize("O2,unroll-loops")

#include <string>
#include <iostream>

using namespace std;

struct PrefixTree {
    static const int N = 1e6 + 10;
    int trie[N][26];
    int cnt[N];
    int idx;

    PrefixTree() :
        idx(0) {}

    void insert(string s) {
        int p = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!trie[p][c])
                trie[p][c] = ++idx;
            p = trie[p][c];
            cnt[p] += 1;
        }
    }

    int query(string s) {
        int p = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!trie[p][c])
                return 0;
            p = trie[p][c];
        }
        return cnt[p];
    }
};

int n, m;
PrefixTree TRIE;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    while (n--) {
        string s;
        cin >> s;
        TRIE.insert(s);
    }

    while (m--) {
        string s;
        cin >> s;
        cout << TRIE.query(s) << '\n';
    }

    fflush(stdout);
    return 0;
}
