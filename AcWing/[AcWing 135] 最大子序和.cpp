#include <deque>
#include <climits>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 3e5 + 10;

int n, m, t;
long long s[N];
long long ans = LONG_MIN;
deque<long long> seg;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> t;
        s[i] = s[i - 1] + t;
    }

    seg.push_back(0); // !!!

    for (int i = 1; i <= n; i++) {
        while (!seg.empty() && i - m > seg.front()) seg.pop_front();
        ans = max(ans, s[i] - s[seg.front()]);
        while (!seg.empty() && s[seg.back()] >= s[i]) seg.pop_back();
        seg.push_back(i);
    }

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
