#include <queue>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 155;
const int M = 75;

int n;
PII ans[N];

struct AhoCorasick {
    int trie[N * M][26];
    int fail[N * M];
    int src[N * M];
    int idx;

    void init() {
        memset(trie, 0, sizeof trie);
        memset(fail, 0, sizeof fail);
        memset(src, 0, sizeof src);
        idx = 0;
    }

    void insert(string s, int x) {
        int p = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!trie[p][c]) trie[p][c] = ++idx;
            p = trie[p][c];
        }
        src[p] = x;
    }

    void set_fail() {
        queue<int> q;

        for (int i = 0; i < 26; i++)
            if (trie[0][i])
                q.push(trie[0][i]);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < 26; i++) {
                int p = trie[u][i];
                if (!p)
                    trie[u][i] = trie[fail[u]][i];
                else {
                    fail[p] = trie[fail[u]][i];
                    q.push(p);
                }
            }
        }
    }

    void query(string s) {
        int len = s.length();
        for (int i = 0, j = 0; i < len; i++) {
            int c = s[i] - 'a';
            int p = trie[j][c];
            j = trie[j][c];
            while (p) {
                ans[src[p]].first++;
                p = fail[p];
            }
        }
    }
} ACA;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n && n) {
        ACA.init();
        for (int i = 1; i <= n; i++) ans[i] = PII(0, 0);

        vector<string> strs(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> strs[i];
            ACA.insert(strs[i], i);
            ans[i] = PII(0, i);
        }

        ACA.set_fail();

        string s;
        cin >> s;

        ACA.query(s);

        int maxcnt = 0;
        vector<int> maxseen;
        for (int i = 1; i <= n; i++)
            if (ans[i].first > maxcnt)
                maxseen.clear(), maxseen.push_back(ans[i].second), maxcnt = ans[i].first;
            else if (ans[i].first == maxcnt)
                maxseen.push_back(ans[i].second);

        cout << maxcnt << endl;
        for (int x : maxseen)
            cout << strs[x] << endl;
    }

    return fflush(stdout), 0;
}
