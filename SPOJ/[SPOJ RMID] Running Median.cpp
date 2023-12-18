#pragma GCC optimize("O3, unroll-loops")

#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using MAXHEAP = __gnu_pbds::priority_queue<int, less<int>>;
using MINHEAP = __gnu_pbds::priority_queue<int, greater<int>>;

namespace FastIO {
    int read() {
        int x = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            x = x * 10 + ch - 48, ch = getchar();
        return x * f;
    }
    void write(int x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}  // namespace FastIO
using namespace FastIO;

MAXHEAP maxpq;
MINHEAP minpq;

void adjust() {
    if (maxpq.size() > minpq.size())
        minpq.push(maxpq.top()), maxpq.pop();
    if (minpq.size() > maxpq.size() + 1)
        maxpq.push(minpq.top()), minpq.pop();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin.peek() != EOF) {
        maxpq.clear(), minpq.clear();

        int t;
        while (cin >> t, t) {
            if (t != -1)
                if (minpq.empty() || t >= minpq.top())
                    minpq.push(t);
                else
                    maxpq.push(t);
            else if ((minpq.size() + maxpq.size()) & 1)
                cout << minpq.top() << '\n', minpq.pop();
            else
                cout << maxpq.top() << '\n', maxpq.pop();
            adjust();
        }
        cout << '\n';
    }

    fflush(stdout);
    return 0;
}
