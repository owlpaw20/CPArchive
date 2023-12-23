#include <vector>
#include <climits>
#include <iostream>
using namespace std;

int n, sum = INT_MIN, ans = INT_MIN;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    while (n--) {
        int t;
        cin >> t;
        sum = max(sum, 0) + t;
        ans = max(sum, ans);
    }
    cout << ans << endl;
    return 0;
}
