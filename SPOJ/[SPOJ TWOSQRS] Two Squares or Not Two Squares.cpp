#include <cmath>
#include <iostream>
using namespace std;
using lng = long long;

int c;

lng pow2(lng x) { return x * x; }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> c;
    while (c--) {
        lng t;
        cin >> t;
        lng sqt = sqrt(t);
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
