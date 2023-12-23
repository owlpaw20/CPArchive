#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int n, m;
unordered_map<string, vector<int>> tb;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        while (t--) {
            string s;
            cin >> s;
            tb[s].push_back(i);
        }
    }
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        unordered_set<int> flag;
        for (int it : tb[s])
            if (flag.insert(it).second)
                cout << it << " ";
        cout << endl;
    }
    return 0;
}
