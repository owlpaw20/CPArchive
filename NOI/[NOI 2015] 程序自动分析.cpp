#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>

#define endl '\n'

struct MyHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

using namespace std;

const int N = 1e5 + 10;

struct Operation {
    bool equality;
    int first_var, second_var;
    bool operator<(const Operation &t) const {
        return equality > t.equality;
    }
};

int T, n, idx, p[N * 2];
unordered_map<int, int, MyHash> tmp;
Operation opt[N];

int find_set(int x) {
    if (p[x] == x) return x;
    return p[x] = find_set(p[x]);
}

void union_sets(int x, int y) {
    int px = find_set(x), py = find_set(y);
    if (px != py) p[px] = py;
}

int address(int x) {
    if (tmp.count(x)) return tmp[x];
    return tmp[x] = ++idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        tmp.clear();
        idx = 0;

        cin >> n;
        for (int i = 1; i <= n; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            opt[i] = (Operation) {
                (bool)c, address(a), address(b)
            };
        }

        for (int i = 1; i <= idx; i++)
            p[i] = i;

        for (int i = 1; i <= n; i++)
            if (opt[i].equality == true)
                union_sets(opt[i].first_var, opt[i].second_var);

        bool flag = true;
        for (int i = 1; i <= n; i++)
            if (opt[i].equality == false)
                if (find_set(opt[i].first_var) == find_set(opt[i].second_var)) {
                    flag = false;
                    break;
                }
        if (flag) puts("YES");
        else puts("NO");
    }

    fflush(stdout);
    return 0;
}
