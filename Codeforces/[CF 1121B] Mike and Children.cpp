#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e3 + 5;
const int M = 2e5 + 5;

int n;
int a[N];
int b[M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 1; j < i; j++)
            b[a[i] + a[j]]++;
    }

    int ans = 0;
    for (int i = 2; i <= 2e5; i++)
        ans = max(ans, b[i]);

    cout << ans << endl;
    fflush(stdout);
    return 0;
}
