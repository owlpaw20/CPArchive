#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;

template <class Type>
struct Queue {
    Type data[N];
    int head = 0, rear = -1;
    void push(Type x) { data[++rear] = x; }
    void pop() { head++; }
    void pop_back() { rear--; }
    Type front() { return data[head]; }
    Type back() { return data[rear]; }
    bool empty() { return head > rear; }
};

int n, k, a[N];
Queue<int> qmx, qmn;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        while (a[i] > a[qmx.back()] && !qmx.empty()) qmx.pop_back();
        while (a[i] < a[qmn.back()] && !qmn.empty()) qmn.pop_back();
        qmx.push(i), qmn.push(i);
        if (i >= k) {
            while (!qmx.empty() && qmx.front() <= i - k) qmx.pop();
            while (!qmn.empty() && qmn.front() <= i - k) qmn.pop();
            cout << a[qmx.front()] << " " << a[qmn.front()] << endl;
        }
    }

    fflush(stdout);
    return 0;
}
