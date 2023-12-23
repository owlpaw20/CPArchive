#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e5 + 10;

int n;
int mn[N];
int sum[N];
int prob[N];
double avg[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(mn, 0x3F, sizeof mn);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> prob[i];

    for (int i = n; i > 0; i--) {
        mn[i] = min(mn[i + 1], prob[i]);
        sum[i] = sum[i + 1] + prob[i];
        avg[i] = 1.0 * (sum[i] - mn[i]) / (n - i);
    }

    double mx = 0;
    for (int i = 1; i <= n; i++)
        mx = max(mx, avg[i]);
    for (int i = 2; i < n; i++)
        if (avg[i] == mx)
            cout << i - 1 << endl;
    return 0;
}
