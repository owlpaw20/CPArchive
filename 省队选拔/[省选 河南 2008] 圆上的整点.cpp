#include <cmath>
#include <iostream>
#include <unordered_map>

using namespace std;
using lng = long long;

int n;
unordered_map<lng, lng> factors;

lng factor(lng x) {
    lng lmt = sqrt(x), ans = 1;
    for (lng i = 2; i <= lmt; i++) {
        int exp = 0;
        while (x % i == 0) exp++, x /= i;
        if (i % 4 == 1) ans *= exp * 2 + 1;
    }
    if (x != 1 && x % 4 == 1) ans *= 3;
    return ans;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    cout << 4 * factor(n) << endl;
    return 0;
}
