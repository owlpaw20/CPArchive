#include <iostream>
#include <unordered_map>
#define endl '\n'

using namespace std;
using i64 = long long;

int n;

bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 2; i <= n; i++)
        if (is_prime(i)) {
            i64 fact = i;
            int exp = 0;
            while (fact <= n)
                exp += n / fact, fact *= i;
            cout << i << ' ' << exp << endl;
        }

    fflush(stdout);
    return 0;
}
