#include <vector>
#include <iostream>
using namespace std;

template <class T>
struct Queue {
    vector<T> data;
    int head, rear;
    void push(T x) {
        data[++rear] = x;
    }
    void pop() {
        head++;
    }
    bool empty() {
        return head > rear;
    }
    void init(int n) {
        head = 0;
        rear = -1;
        data.clear();
        data.resize(n);
    }
    Queue() {}
    Queue(int n) {
        init(n);
    }
};

const int N = 1e5 + 10;

int n, m;
int stars[N];
Queue<int> window(N);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int maxt = 0;
    for (int i = 1; i <= n; i++) {
        int t, b;
        cin >> t >> b;
        stars[t] += b;
        maxt = max(maxt, t);
    }

    int current = 0;
    for (int i = 1; i <= m; i++)
        window.push(stars[i]), current += stars[i];

    int ans = current;
    for (int i = m + 1; i <= maxt; i++) {
        current -= stars[i - m];
        window.pop();
        window.push(stars[i]);
        current += stars[i];
        ans = max(ans, current);
    }

    cout << ans << endl;
    return 0;
}
