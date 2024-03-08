#include <string>
#include <iostream>
#include <unordered_map>
#define endl '\n'
using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

int n;
int seq[N], tmp[N];
unordered_map<string, int> Hash;

i64 count_invs(int l, int r) {
    if (l >= r)
        return 0LL;

    int mid = (l + r) >> 1;
    i64 inv = count_invs(l, mid) + count_invs(mid + 1, r);

    int lx = l, rx = mid + 1, tx = 0;
    while (lx <= mid && rx <= r)
        if (seq[lx] <= seq[rx]) {
            tmp[tx++] = seq[lx++];
            inv += rx - mid - 1;
        } else
            tmp[tx++] = seq[rx++];
    while (lx <= mid) tmp[tx++] = seq[lx++], inv += r - mid;
    while (rx <= r) tmp[tx++] = seq[rx++];

    for (int i = l, j = 0; i <= r; i++, j++)
        seq[i] = tmp[j];

    return inv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        Hash[s] = i;
    }

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        seq[i] = Hash[s];
    }

    cout << count_invs(1, n) << endl;
    fflush(stdout);
    return 0;
}
