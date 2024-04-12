#include <queue>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;

struct Flight {
    int arrvl, deprt;
    bool operator<(const Flight &t) const {
        if (arrvl != t.arrvl) return arrvl > t.arrvl;
        return deprt > t.deprt;
    }
};

int n, m1, m2, ans;
Flight dmst[N], intl[N];
int dmst_used[N], intl_used[N];

bool cmp(Flight x, Flight y) {
    if (x.arrvl != y.arrvl) return x.arrvl < y.arrvl;
    return x.deprt < y.deprt;
}

void solve(Flight *f, int total, int *used) {
    priority_queue<Flight> flights;
    priority_queue<int, vector<int>, greater<int>> bridges;

    for (int i = 1; i <= n; i++) bridges.push(i);
    for (int i = 1; i <= total; i++) {
        while (!flights.empty() && flights.top().arrvl <= f[i].arrvl) {
            bridges.push(flights.top().deprt);
            flights.pop();
        }
        if (!bridges.empty()) {
            int b = bridges.top();
            bridges.pop();
            used[b]++;
            flights.push((Flight){
                f[i].deprt, b});
        }
    }

    for (int i = 1; i <= n; i++) used[i] += used[i - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m1 >> m2;
    for (int i = 1; i <= m1; i++)
        cin >> dmst[i].arrvl >> dmst[i].deprt;
    for (int i = 1; i <= m2; i++)
        cin >> intl[i].arrvl >> intl[i].deprt;

    sort(dmst + 1, dmst + m1 + 1, cmp);
    sort(intl + 1, intl + m2 + 1, cmp);

    solve(dmst, m1, dmst_used);
    solve(intl, m2, intl_used);

    for (int i = 0; i <= n; i++)
        ans = max(ans, dmst_used[i] + intl_used[n - i]);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
