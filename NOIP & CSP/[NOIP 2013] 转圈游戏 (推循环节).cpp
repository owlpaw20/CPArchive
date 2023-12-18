#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

int n, m, K, x;
vector<int> loop;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K >> x;

    int now = x;
    do {
        loop.push_back(now);
        now = (now + m) % n;
    } while (now != x);

    int l = K / 10;
    int r = K % 10;
    int len = loop.size();
    lng q = 1;

    for (int i = 1; i <= l; i++) q = q * (lng)1e10 % len;
    for (int i = 1; i <= r; i++) q = q * 10 % len;

    cout << loop[q] << endl;
    fflush(stdout);
    return 0;
}
