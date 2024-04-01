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

    // 插入向字典树中插入模式串
    void insert(string s) {
        int p = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!trie[p][c]) trie[p][c] = ++idx;
            p = trie[p][c];
        }
        cnt[p]++;
    }

    // 求模式串所有节点的 fail 指针
    void set_fail() {
        queue<int> q;

        // 第一层的节点的 fail 指针都默认为 0，直接加入队伍准备搜索
        for (int i = 0; i < 26; i++)
            if (trie[0][i])
                q.push(trie[0][i]);

        // BFS 保证了一次搜一层，保证所有 fail 指针只会指向上层节点
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int i = 0; i < 26; i++) { // 枚举当前节点的所有子节点
                int p = trie[u][i];
                if (p) { // 如果存在该字符
                    int j = fail[u]; // 则定位到当前节点的 fail 指针
                    while (j && !trie[j][i]) j = fail[j]; // 并根据 fail 指针不断向前跳
                    if (trie[j][i]) j = trie[j][i]; // 直到回到根节点或者找到匹配的字符
                    fail[p] = j; // 找到合法最长前缀
                    q.push(p); // 将该节点加入队列中准备搜索
                }
            }
        }
    }

    // 统计所有模式串在某字符串 s 中出现的总次数
    int query(string s) {
        int ans = 0;
        int len = s.length();
        for (int i = 0, j = 0; i < len; i++) { // 用 i 指针遍历待匹配串
            int c = s[i] - 'a'; // 获取当前字符
            while (j && !trie[j][c]) j = fail[j]; // 跳到最高层的 fail 指针
            if (trie[j][c]) j = trie[j][c]; // 进入下一个字符
            int p = j;
            while (p) { // 如果找到合法匹配
                ans += cnt[p]; // 则累加当前单词被重复的次数（上跳后还要计算是为了统计包含在当前模式串中的其他子模式串的出现）
                cnt[p] = 0; // 并将该单词的计数归零避免重复统计（本题要求）
                p = fail[p]; // 向上跳
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
