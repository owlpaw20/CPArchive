#include <numeric>
#include <iostream>
#include <unordered_set>

#define endl '\n'

using namespace std;

int a, b, c;
unordered_set<int> vis;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c;
    a %= b;

    int digits = 1;

    while (true) {
        a *= 10;

        int quo = a / b;
        int rmd = a % b;

        if (quo == c) {
            cout << digits << endl;
            exit(0);
        }

        if (!vis.insert(rmd).second)
            break;

        a %= b, digits++;
    }

    cout << -1 << endl;
    fflush(stdout);
    return 0;
}
