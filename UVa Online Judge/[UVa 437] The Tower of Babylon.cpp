#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 40;

struct Block {
    int x, y, z;
    Block(int a, int b, int c) :
        x(a), y(b), z(c) {}
    bool operator<(const Block &t) const {
        return (x > t.x && y > t.y) || (x > t.y && y > t.x);
    }
};

int n, f[3 * N], cnt;
vector<Block> b;

int MDFS(int idx) {
    if (f[idx] > 0)
        return f[idx];
    f[idx] = b[idx].z;
    for (int i = 0; i < 3 * n; i++)
        if (b[i] < b[idx])
            f[idx] = max(f[idx], MDFS(i) + b[idx].z);
    return f[idx];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (++cnt) {
        b.clear();
        memset(f, 0, sizeof f);
        cin >> n;
        if (n == 0) break;
        for (int i = 1; i <= n; i++) {
            int a, bb, c;
            cin >> a >> bb >> c;
            b.emplace_back(a, bb, c);
            b.emplace_back(a, c, bb);
            b.emplace_back(bb, c, a);
        }
        int ans = 0;
        for (int i = 0; i < 3 * n; i++)
            ans = max(ans, MDFS(i));
        printf("Case %d: maximum height = %d\n", cnt, ans);
    }

    return 0;
}
