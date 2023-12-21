#include <set>
#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;
using ITER = set<lng>::iterator;

int n;
set<lng> tr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    tr.insert(INT_MIN);
    tr.insert(INT_MAX);

    cin >> n;

    lng ans = 0LL;

    while (n--) {
        int x;
        cin >> x;
        if (tr.size() == 2) {
            ans += x;
            tr.insert(x);
        } else {
            ITER a = tr.lower_bound(x);
            if (x != *a) {
                ITER b = a;
                ans += min(abs(*a - x), abs(*(--b) - x));
                tr.insert(x);
            }
        }
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
