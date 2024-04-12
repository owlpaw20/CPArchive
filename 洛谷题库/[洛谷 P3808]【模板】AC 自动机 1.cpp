#include <queue>
#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e6 + 5;

struct AhoCorasick {
    int trie[N][26];
    int fail[N];
    int cnt[N];
    int idx;

    void insert(string s) {
        int p = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!trie[p][c]) trie[p][c] = ++idx;
            p = trie[p][c];
        }
        cnt[p]++;
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

    int query(string s) {
        int len = s.length(), ret = 0;
        for (int i = 0, j = 0; i < len; i++) {
            int c = s[i] - 'a';
            int p = j = trie[j][c];
            while (p && ~cnt[p]) {  // 如果已经统计过，就不需要继续往上跳了
                ret += cnt[p];
                cnt[p] = -1;
                p = fail[p];
            }
        }
        return ret;
    }
};

int n;
AhoCorasick ACA;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        ACA.insert(s);
    }

    ACA.set_fail();

    string s;
    cin >> s;
    cout << ACA.query(s) << endl;

    return fflush(stdout), 0;
}
