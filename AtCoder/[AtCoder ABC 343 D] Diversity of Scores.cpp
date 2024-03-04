#include <map>
#include <iostream>

#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e5 + 5;

int n, T;
i64 scores[N];
map<i64, int> vis;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T;
    vis[0] = n;

    while (T--) {
        int x, y;
        cin >> x >> y;

        vis[scores[x]]--;
        if (!vis[scores[x]]) vis.erase(scores[x]);
        scores[x] += y;
        vis[scores[x]]++;

        cout << vis.size() << endl;
    }

    return fflush(stdout), 0;
}
