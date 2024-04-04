#include <iostream>
using namespace std;

typedef long long ll;
const int N = 15;

int n, mod[N], rem[N];
ll prod = 1, Mi, ans;

void extend_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return;
    }
    extend_gcd(b, a % b, y, x);
    y -= a / b * x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> mod[i] >> rem[i];
        prod *= mod[i];
    }

    for (int i = 1; i <= n; i++) {
        Mi = prod / mod[i];
        ll x = 0, y = 0;
        extend_gcd(Mi, mod[i], x, y);
        ans += rem[i] * Mi * (x < 0 ? x + mod[i] : x);
    }

    cout << ans % prod << endl;
    return 0;
}
