#include <vector>
#include <iostream>
#include <algorithm>
#define left first
#define right second
using namespace std;
using PII = pair<int, int>;

const int NINF = 0x80000000;

int n;
vector<PII> intvl;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    intvl.resize(n);
    for (int i = 0; i < n; i++)
        cin >> intvl[i].left >> intvl[i].right;

    sort(intvl.begin(), intvl.end());

    int L = NINF, R = NINF, ans = 0;
    for (int i = 0; i < n; i++) {
        auto [l, r] = intvl[i];
        if (R < l)
            L = l, R = r, ans++;
        else if (R < r)
            R = r;
    }
    cout << ans << endl;
    return 0;
}
