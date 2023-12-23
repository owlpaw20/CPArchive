#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

int a, b;

void exgcd(lng a, lng b, lng& x, lng& y) {
    if (b == 0)
        return (void)(x = 1, y = 0);
    exgcd(b, a % b, x, y);
    lng tmp = y;
    y = x - a / b * y;
    x = tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    lng x = 0, y = 0;
    exgcd(a, b, x, y);

    cout << (x % b + b) % b << endl;

    fflush(stdout);
    return 0;
}
