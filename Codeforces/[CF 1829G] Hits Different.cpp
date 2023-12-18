#include <iostream>

using namespace std;
using Long = long long;

const int N = 2e3 + 50;

Long t, idx = 1, cans[N][N], f[N * N];

void precompute() {
    f[idx++] = cans[1][1] = 1;
    for (Long i = 2; i <= 2023; i++)
        for (Long j = 1; j <= i; j++) {
            cans[i][j] = idx * idx + cans[i - 1][j - 1] + cans[i - 1][j] - cans[i - 2][j - 1];
            f[idx++] = cans[i][j];
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    precompute();

    while (t--) {
        int n;
        cin >> n;
        cout << f[n] << endl;
    }

    return 0;
}
