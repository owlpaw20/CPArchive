#include <vector>
#include <iostream>
#include <algorithm>
#define left first
#define right second
using namespace std;
using PII = pair<int, int>;

const int INF = 0x7FFFFFFF;

int n;
vector<PII> intvl;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    intvl.resize(n);
    for (int i = 0; i < n; i++)
        cin >> intvl[i].left >> intvl[i].right;

    auto cmp = [&](PII a, PII b) { return a.right > b.right; };
    sort(intvl.begin(), intvl.end(), cmp);

    int L = INF, R = INF, ans = 0;
    for (int i = 0; i < n; i++) {
        auto [l, r] = intvl[i];
        if (L > r)
            L = l, R = r, ans++;
        else if (L > l)
            L = l;
    }
    cout << ans << endl;
    return 0;
}
