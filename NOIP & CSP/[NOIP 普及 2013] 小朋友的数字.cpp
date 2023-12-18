#include <vector>
#include <climits>
#include <iostream>

using namespace std;
using lng = __int128;

int n, p;

void print(lng x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;

    lng sum = LONG_LONG_MIN, maxsum = LONG_LONG_MIN;
    vector<lng> f(n);

    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        sum = max(sum, (lng)0) + t;
        maxsum = max(maxsum, sum);
        f[i] = maxsum;
    }

    lng ans = f[0], score = f[0] + f[0];
    for (int i = 1; i < n; i++) {
        ans = max(ans, score);
        if (f[i] > 0) score += f[i];
    }

    print(ans % p), putchar('\n');
    return 0;
}
