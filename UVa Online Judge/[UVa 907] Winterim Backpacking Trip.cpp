#include <cstring>
#include <iostream>

using namespace std;

const int N = 6e2 + 10;
const int INF = 0x7FFFFFFF;

int n, K, dist[N];

bool check(int x) {
    int trv = 0, d = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (dist[i] > x) return false;  // 如果距离已经超过，则不可能达到下一个营地
        trv += dist[i];                 // 加上到达下一个营地的总距离
        if (trv > x)                    // 如果总距离超过今天所能行进的距离
            d += 1, trv = dist[i];      // 则度过一晚上
    }
    return d <= K;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> K) {
        memset(dist, 0, sizeof dist);
        for (int i = 1; i <= n + 1; i++)
            cin >> dist[i];

        int l = 1, r = 1e9;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid + 1;
        }

        cout << r << '\n';
    }

    fflush(stdout);
    return 0;
}
