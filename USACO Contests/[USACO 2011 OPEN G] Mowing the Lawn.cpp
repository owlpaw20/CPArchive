#include <iostream>

using namespace std;
using i64 = long long;

const int N = 1e5 + 10;

template <class Type>
struct Queue {
    Type data[N];
    int head, rear;
    void push(Type x) { data[++rear] = x; }
    void pop_front() { head++; }
    void pop_back() { rear--; }
    Type front() { return data[head]; }
    Type back() { return data[rear]; }
    bool empty() { return head > rear; }
    Queue() : head(0), rear(0) {}
};

int n, k, e[N];
i64 pre[N], f[N], d[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    Queue<int> q;
    for (int i = 1; i <= n; i++) {
        cin >> e[i];
        pre[i] = pre[i - 1] + e[i];
    }

    for (int i = 1; i <= n; i++) {
        d[i] = f[i - 1] - pre[i];
        while (!q.empty() && d[q.back()] < d[i]) q.pop_back();
        q.push(i);
        while (q.front() < i - k) q.pop_front();
        f[i] = d[q.front()] + pre[i];
    }

    cout << f[n] << endl;
    return 0;
}
