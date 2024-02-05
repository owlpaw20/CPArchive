#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

int a, b;

void extend_gcd(lng a, lng b, lng& x, lng& y) {
    if (b == 0) return (void)(x = 1, y = 0);
    extend_gcd(b, a % b, y, x);
    y -= a / b * x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    lng x, y;
    extend_gcd(a, b, x, y);

    cout << (x % b + b) % b << endl;
    return fflush(stdout), 0;
}
