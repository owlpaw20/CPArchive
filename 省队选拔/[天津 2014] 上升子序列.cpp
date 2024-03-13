#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;

const int MAX_N = 1e5 + 5;
const int MOD = 1e9 + 7;

int N;
int a[MAX_N];
std::vector<int> disc;

struct FenwickTree {
    int tr[MAX_N];

    void update(int x, int val) {
        for (; x <= N; x += x & (-x))
            tr[x] = (tr[x] + val) % MOD;
    }

    int query(int x) {
        int sum = 0;
        for (; x; x -= x & (-x))
            sum = (sum + tr[x]) % MOD;
        return sum;
    }
} FWK;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> a[i], disc.emplace_back(a[i]);

    std::sort(disc.begin(), disc.end());
    disc.erase(std::unique(disc.begin(), disc.end()), disc.end());

    for (int i = 1; i <= N; i++)
        a[i] = std::lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin() + 1;

    for (int i = 1; i <= N; i++) {
        int tmp = FWK.query(a[i]) - FWK.query(a[i] - 1);
        FWK.update(a[i], FWK.query(a[i] - 1));
        if (tmp) FWK.update(a[i], -tmp);
        FWK.update(a[i], 1);
    }

    cout << FWK.query(disc.size()) - disc.size() << endl;
    return fflush(stdout), 0;
}
