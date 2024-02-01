#include <cmath>
#include <iostream>

#define endl '\n'

using namespace std;
using lng = long long;

const int N = 1e5 + 5;
const int M = 4e2 + 5;

int n, q, len;
int a[N];
lng sum[N], add[N];

void update(int l, int r, lng x) {
    if (l / len == r / len)
        for (int i = l; i <= r; i++)
            a[i] += x, sum[l / len] += x;
    else {
        int i = l, j = r;
        while (i / len == l / len) a[i] += x, sum[i / len] += x, i++;
        while (j / len == r / len) a[j] += x, sum[j / len] += x, j--;
        for (int k = i / len; k <= j / len; k++)
            sum[k] += x * len, add[k] += x;
    }
}

lng query(int l, int r) {
    lng ret = 0;

    if (l / len == r / len)
        for (int i = l; i <= r; i++)
            ret += a[i] + add[i / len];
    else {
        int i = l, j = r;
        while (i / len == l / len) ret += a[i] + add[i / len], i++;
        while (j / len == r / len) ret += a[j] + add[j / len], j--;
        for (int k = i / len; k <= j / len; k++) ret += sum[k];
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    len = sqrt(n);

    for (int i = 1; i <= n; i++)
        cin >> a[i], sum[i / len] += a[i];

    while (q--) {
        char type;
        int l, r, x;

        cin >> type >> l >> r;

        if (type == 'C') {
            cin >> x;
            update(l, r, x);
        } else
            cout << query(l, r) << endl;
    }

    return fflush(stdout), 0;
}
