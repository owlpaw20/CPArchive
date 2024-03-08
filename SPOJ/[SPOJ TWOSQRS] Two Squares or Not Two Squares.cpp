#include <cmath>
#include <iostream>
using namespace std;
using i64 = long long;

int c;

i64 pow2(i64 x) { return x * x; }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> c;
    while (c--) {
        i64 t;
        cin >> t;
        i64 sqt = sqrt(t);
        bool flag = false;
        for (int i = 0; i <= sqt; i++)
            if (pow2(i) + pow2(sqrt(t - pow2(i))) == t) {
                flag = true;
                puts("Yes");
                break;
            }
        if (!flag) puts("No");
    }
    return 0;
}
