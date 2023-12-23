#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int L, n, K;
int signs[N];

bool check(int x) {
    int emptiness = K;
    int pos = 0;
    for (int i = 2; i <= n; i++) {
        if (emptiness < 0) break;
        if (signs[i] - pos <= x) {
            pos = signs[i];
        } else {
            pos += x;
            i--, emptiness--;
        }
    }
    return (emptiness >= 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> n >> K;
    for (int i = 1; i <= n; i++)
        cin >> signs[i];

    int l = 0, r = L;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << r << endl;
    return 0;
}
