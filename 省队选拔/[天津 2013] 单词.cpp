#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e6 + 5;
const int M = 2e2 + 5;

int n;

struct AhoCorasick {
    int trie[N][26];
    int fail[N];
    int cnt[N];
    int tar[M];
    int f[N];
    int q[N];
    int idx;

    void insert(string s, int x) {
        int p = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!trie[p][c]) trie[p][c] = ++idx;
            p = trie[p][c];
            f[p]++;
        }
        cnt[p]++;
        tar[x] = p;
    }

    void set_fail() {
        int h = 0, t = -1;

        for (int i = 0; i < 26; i++)
            if (trie[0][i])
                q[++t] = trie[0][i];

        while (h <= t) {
            int u = q[h++];
            for (int i = 0; i < 26; i++) {
                int p = trie[u][i];
                if (!p)
                    trie[u][i] = trie[fail[u]][i];
                else {
                    fail[p] = trie[fail[u]][i];
                    q[++t] = p;
                }
            }
        }
    }

    void query() {
        for (int i = idx - 1; ~i; i--) f[fail[q[i]]] += f[q[i]];
        for (int i = 1; i <= n; i++) cout << f[tar[i]] << endl;
    }
} ACA;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        ACA.insert(s, i);
    }

    ACA.set_fail();
    ACA.query();

    return fflush(stdout), 0;
}
