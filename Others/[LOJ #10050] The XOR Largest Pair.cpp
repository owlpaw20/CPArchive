#include <iostream>
using namespace std;

const int N = 1e5 + 10;

struct PrefixTree {
    int t[31 * N][2] = {0}, idx = 0;
    void insert(int x) {
        int p = 0;
        for (int i = 30; ~i; i--) {
            int c = (x >> i) & 1;
            if (!t[p][c]) t[p][c] = ++idx;
            p = t[p][c];
        }
    }
    int get_max_xor(int x) {
        int p = 0, res = 0;
        for (int i = 30; ~i; i--) {
            int c = (x >> i) & 1;
            if (t[p][!c]) {
                res += (1 << i);
                p = t[p][!c];
            } else
                p = t[p][c];
        }
        return res;
    }
};

int n, a[N];
PrefixTree trie;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        trie.insert(a[i]);
    }
    int ans = -1;
    for (int i = 1; i <= n; i++)
        ans = max(trie.get_max_xor(a[i]), ans);
    cout << ans << endl;
    return 0;
}
