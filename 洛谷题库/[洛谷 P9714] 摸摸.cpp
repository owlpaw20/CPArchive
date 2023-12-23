#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
using VI = vector<int>;

const int N = 2000 + 10;

int T;
bool flag;

VI operator+(VI x, VI y) {
    VI ret(x.size());
    for (int i = 0; i < x.size(); i++)
        ret[i] = x[i] + y[i];
    return ret;
}

bool operator>(VI x, VI y) {
    for (int i = 0; i < x.size(); i++)
        if (x[i] > y[i])
            return true;
    return false;
}

void DFS(VI a, VI b, VI t, bool o) {
    if (a >= b) {
        if (a == b)
            flag = true;
        return;
    }
    DFS(a + t, b, t, o);
    if (o == false) {
        VI tmp = t;
        reverse(tmp.begin(), tmp.end());
        tmp = t + tmp;
        DFS(a, b, tmp, true);
    }
}

void solve() {
    int n;
    cin >> n;
    VI a(n, 0), t(n, 0), b(n, 0);
    flag = false;
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    DFS(a, b, t, false);
    cout << (flag ? "Yes" : "No") << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> T;
    while (T--) solve();
    return 0;
}
