#include <iostream>
using namespace std;

const int N = 600 + 1;

int n, w, vis[N];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        vis[t]++;
        int cnt = 0, lmt = max(1, i * w / 100);
        for (int j = 600; ~j; j--) {
            cnt += vis[j];
            if (cnt >= lmt) {
                cout << j << " ";
                break;
            }
        }
    }
    cout << endl;
    return 0;
}
