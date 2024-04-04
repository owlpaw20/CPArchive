#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
const int M = 2e5 + 10;

struct Comp {
    int s, w, id;
    bool operator<(const Comp &t) const {
        if (s != t.s) return s > t.s;
        return id < t.id;
    }
};

int n, r, q;
Comp a[M], w[N], l[N];

void merge() {
    int ws = 0, ls = 0;
    for (int i = 2; i <= 2 * n; i += 2) {
        if (a[i - 1].w < a[i].w) {
            a[i].s++;
            w[++ws] = a[i], l[++ls] = a[i - 1];
        } else {
            a[i - 1].s++;
            w[++ws] = a[i - 1], l[++ls] = a[i];
        }
    }
    int pos = 1;
    ws = ls = 1;
    while (ws <= n && ls <= n)
        if (w[ws] < l[ls])
            a[pos++] = w[ws++];
        else
            a[pos++] = l[ls++];
    while (ws <= n) a[pos++] = w[ws++];
    while (ls <= n) a[pos++] = l[ls++];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> r >> q;
    for (int i = 1; i <= 2 * n; i++) cin >> a[i].s, a[i].id = i;
    for (int i = 1; i <= 2 * n; i++) cin >> a[i].w;
    sort(a + 1, a + 2 * n + 1);
    while (r--) merge();
    cout << a[q].id << endl;
    return 0;
}
