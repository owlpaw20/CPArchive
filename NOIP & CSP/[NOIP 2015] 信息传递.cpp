#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, ans(INF);
vector<int> p(N);

int find(int x, int &len) {
    len += 1;
    if (p[x] == x) return x;
    return find(p[x], len);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) p[i] = i;

    for (int i = 1; i <= n; i++) {
        int t, len(0);
        cin >> t;
        if (find(t, len) == i)
            ans = min(ans, len);
        else
            p[i] = t;
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
