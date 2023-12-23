#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 3e6 + 10;
int T, trie[N][120], cnt[N], idx, n, q;
string s;

int letter_to_number(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    return c - '0' + 52;
}

void insert(string s) {
    int p = 0, len = s.size();
    for (int i = 0; i < len; i++) {
        int u = letter_to_number(s[i]);
        if (!trie[p][u]) trie[p][u] = ++idx;
        p = trie[p][u];
        cnt[p]++;
    }
    return;
}

int find(string s) {
    int p = 0, len = s.size();
    for (int i = 0; i < len; i++) {
        int u = letter_to_number(s[i]);
        if (!trie[p][u]) return 0;
        p = trie[p][u];
    }
    return cnt[p];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) {
        for (int i = 0; i <= idx; i++)
            for (int j = 0; j < 120; j++)
                trie[i][j] = 0;
        for (int i = 0; i <= idx; i++) cnt[i] = 0;
        idx = 0;
        cin >> n >> q;
        while (n--) {
            cin >> s;
            insert(s);
        }
        while (q--) {
            cin >> s;
            cout << find(s) << endl;
        }
    }
    return 0;
}
