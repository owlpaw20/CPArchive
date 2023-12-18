#include <tuple>
#include <bitset>
#include <vector>
#include <iostream>

using namespace std;
using TPL = tuple<int, int, int>;

const int N = 3e3 + 10;

int n;
int cand[N][6];
vector<TPL> poss;

void prep() {
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
            for (int k = 0; k < 32; k++)
                if ((i | j | k) == 31)
                    poss.emplace_back(i, j, k);
}

bool check(int x) {
    bitset<32> st(0);
    for (int i = 1; i <= n; i++) {
        int status = 0;
        for (int j = 0; j < 5; j++)
            if (cand[i][j + 1] >= x)
                status |= (1 << j);
        st[status] = 1;
    }
    for (TPL p : poss) {
        auto [u, v, w] = p;
        if (st[u] && st[v] && st[w])
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    prep();

    cin >> n;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 5; j++)
            cin >> cand[i][j];

    int l = 1, r = 1e9, ans;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else
            r = mid - 1;
    }

    cout << ans << endl;
    return 0;
}
