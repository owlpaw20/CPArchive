#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int T;

void solve() {
    int n;
    vector<pair<string, int>> vc;
    unordered_map<string, int> mp;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string t;
        getline(cin, t);
        if (t.empty()) {
            i--;
            continue;
        }
        mp[t]++;
    }
    for (auto it : mp)
        vc.emplace_back(it.first, it.second);
    sort(vc.begin(), vc.end());
    for (auto it : vc)
        cout << it.first << " " << it.second << endl;
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> T;
    while (T--) solve();
    return 0;
}
