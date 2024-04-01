#include <cctype>
#include <string>
#include <cstring>
#include <iostream>
#define endl '\n'
using namespace std;
using i64 = long long;

struct Fenwick {
    static const int N = 1e5 + 10;
    int fenwick[N];
    int n;

    void init(int _n) {
        n = _n;
    }
    int lowbit(int x) {
        return x & -x;
    }
    int query(int x) {
        int ret = 0;
        for (int i = x; i; i -= lowbit(i))
            ret += fenwick[i];
        return ret;
    }
    void update(int x, int delta) {
        for (int i = x; i <= n; i += lowbit(i))
            fenwick[i] += delta;
    }
};

struct PrefixTree {
    static const int N = 5e5 + 10;
    int trie[N][55];
    int cnt[N];
    int idx;

    PrefixTree() : idx(0) {}
    int to_number(char ch) {
        if (islower(ch)) return ch - 'a';
        return ch - 'A' + 26;
    }
    void insert(string s, int rank) {
        int p = 0;
        for (char ch : s) {
            int c = to_number(ch);
            if (!trie[p][c])
                trie[p][c] = ++idx;
            p = trie[p][c];
        }
        cnt[p] = rank;
    }
    int query(string s) {
        int p = 0;
        for (char ch : s) {
            int c = to_number(ch);
            p = trie[p][c];
        }
        return cnt[p];
    }
};

const int N = 1e5 + 10;

int n;
int seq[N];
Fenwick fenwick;
PrefixTree trie;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    fenwick.init(n + 5);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        trie.insert(s, i);
    }

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        seq[i] = trie.query(s);
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        fenwick.update(seq[i], 1);
        ans += (i - fenwick.query(seq[i]));
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
