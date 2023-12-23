#include <deque>
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1e6 + 10;
int n, k, a[N];
deque<int> wd;

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        while (!wd.empty() && a[wd.back()] > a[i])
            wd.pop_back();
        wd.push_back(i);
        if (i >= k) {
            while (!wd.empty() && wd.front() <= i - k)
                wd.pop_front();
            cout << a[wd.front()] << " ";
        }
    }
    cout << endl;
    while (!wd.empty()) wd.pop_front();
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        while (!wd.empty() && a[wd.back()] < a[i])
            wd.pop_back();
        wd.push_back(i);
        if (i >= k) {
            while (!wd.empty() && wd.front() <= i - k)
                wd.pop_front();
            cout << a[wd.front()] << " ";
        }
    }
    cout << endl;
    return 0;
}
