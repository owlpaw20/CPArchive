#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e2 + 10;
const int LMT = 1e6;

int n, K, a[N];
int have[N], prereq[N][N], cnt[N];
int need[N];

bool check(int x) {
    memset(need, 0, sizeof need);
    need[n] = x;

    for (int i = n; i > 0; i--) {
        have[i] = a[i];

        if (need[i] > LMT)
            return false;

        if (need[i] <= have[i]) {
            have[i] -= need[i];
            continue;
        }

        if (!cnt[i])
            return false;

        for (int j = 1; j <= cnt[i]; j++)
            need[prereq[i][j]] += need[i] - have[i];
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    cin >> K;
    while (K--) {
        int prod;
        cin >> prod, cin >> cnt[prod];
        for (int i = 1; i <= cnt[prod]; i++)
            cin >> prereq[prod][i];
    }

    int l = 0, r = LMT;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    cout << l << endl;
    fflush(stdout);
    return 0;
}
