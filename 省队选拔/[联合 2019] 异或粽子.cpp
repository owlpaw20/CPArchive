#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
using Long = long long;
using PLI = pair<Long, int>;
using pair_heap = __gnu_pbds::priority_queue<PLI>;
// first = index, second = value

const int N = 5e5 + 10;

struct PrefixTree {
    Long t[32 * N][2] = {0}, cnt[32 * N] = {0}, idx = 0;
    void insert(Long x) {
        int p = 0;
        for (int i = 31; i >= 0; i--) {
            Long c = (x >> i) & 1;
            if (!t[p][c]) t[p][c] = ++idx;
            p = t[p][c];
            cnt[p]++;
        }
    }
    Long find(Long x, int rank) {
        int p = 0;
        Long res = 0;
        for (int i = 31; i >= 0; i--) {
            int c = (x >> i) & 1;
            if (!t[p][!c])
                p = t[p][c];
            else if (rank <= cnt[t[p][!c]])  // 如果反着走能够找到足够多的数
                p = t[p][!c], res += (1ll << i);
            else  // 上一位不同时一定比相同时的异或和更大
                rank -= cnt[t[p][!c]], p = t[p][c];
        }
        return res;
    }
};

Long p[N];
int n, k, current_rank[N];
PrefixTree trie;
pair_heap heap;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> k;
    k <<= 1;
    trie.insert(p[0] = 0);
    for (int i = 1; i <= n; i++) {
        Long t;
        cin >> t;
        p[i] = p[i - 1] ^ t;
        trie.insert(p[i]);
    }
    for (int i = 0; i <= n; i++) {
        Long t = trie.find(p[i], current_rank[i] = 1);
        heap.push({t, i});
    }
    Long ans = 0;
    while (k--) {
        PLI t = heap.top();
        heap.pop();
        int idx = t.second;
        ans += t.first;
        Long tmp = trie.find(p[idx], ++current_rank[idx]);
        heap.push({tmp, idx});
    }
    cout << (ans >> 1) << endl;
    return 0;
}
