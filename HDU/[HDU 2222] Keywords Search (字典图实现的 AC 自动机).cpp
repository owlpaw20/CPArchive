#include <queue>
#include <string>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e4 + 5;
const int S = 55;

struct AhoCorasick {
    int trie[N * S][26];
    int fail[N * S];
    int cnt[N * S];
    int idx;

    void init() {
        memset(trie, 0, sizeof trie);
        memset(fail, 0, sizeof fail);
        memset(cnt, 0, sizeof cnt);
        idx = 0;
    }

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
                    trie[u][i] = trie[fail[u]][i];  // 把不存在的字符跳回最初的位置
                else {
                    fail[p] = trie[fail[u]][i];  // 把存在的字符直接跳到目标位置
                    q.push(p);
                }
            }
        }
    }

    int query(string s) {
        int ans = 0;
        for (int i = 0, j = 0; s[i]; i++) {
            int c = s[i] - 'a';
            int p = j = trie[j][c];  // 直接跳到最长前缀的位置
            while (p) {
                ans += cnt[p];
                cnt[p] = 0;
                p = fail[p];
            }
        }
        return ans;
    }
};

int n;
AhoCorasick ACA;

void solve() {
    cin >> n;

    ACA.init();

    while (n--) {
        string s;
        cin >> s;
        ACA.insert(s);
    }

    ACA.set_fail();

    string s;
    cin >> s;
    cout << ACA.query(s) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return fflush(stdout), 0;
}
