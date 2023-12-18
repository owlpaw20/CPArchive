#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;

const int N = 1e7 + 10;

int T, idx, pre[N];
bool num[N];

void init() {
    for (int i = 1; i <= 1e7; i++) {
        if (num[i] == true) continue;
        bool flag = true;
        int t = i;
        while (t) {
            if (t % 10 == 7) {
                flag = false;
                break;
            }
            t /= 10;
        }
        num[i] = !flag;
        if (num[i])
            for (int j = 2; i * j <= 1e7; j++)
                num[i * j] = true;
    }

    for (int i = 1; i <= 1e7; i++)
        if (!num[i])
            pre[++idx] = i;
}

int solve(int x) {
    if (num[x]) return -1;
    int pos = upper_bound(pre + 1, pre + idx + 1, x) - pre;
    if (pos > idx) return 1e7 + 1;
    return pre[pos];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();

    cin >> T;
    while (T--) {
        int x;
        cin >> x;
        cout << solve(x) << endl;
    }

    fflush(stdout);
    return 0;
}
