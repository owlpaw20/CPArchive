#include <queue>
#include <iostream>
using namespace std;

int n, w;
priority_queue<int, vector<int>, less<int>> mx;
priority_queue<int, vector<int>, greater<int>> mn;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        if (mn.empty() || t >= mn.top())
            mn.push(t);
        else
            mx.push(t);
        int line = max(1, i * w / 100);
        while (mn.size() > line)
            mx.push(mn.top()), mn.pop();
        while (mn.size() < line)
            mn.push(mx.top()), mx.pop();
        cout << mn.top() << " ";
    }
    cout << endl;
    return 0;
}
