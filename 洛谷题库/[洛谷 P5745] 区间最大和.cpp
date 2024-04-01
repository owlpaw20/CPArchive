#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 4e6 + 10;

struct Queue {
    int e[N], head, rear;
    void push(int x) {
        e[++rear] = x;
    }
    void pop() {
        head++;
    }
    bool empty() {
        return head > rear;
    }
    Queue() : head(0), rear(-1) {
        memset(e, 0, sizeof e);
    }
};

int n, m, l = 1, sum, a[N];
int ansl, ansr, anss;
Queue q;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        q.push(a[i]);
        sum += a[i];
        while (sum > m && !q.empty()) {
            q.pop();
            sum -= a[i];
            if (sum > anss) {
                anss = sum;
                ansl = l;
                ansr = i - 1;
            }
            sum += a[i];
            sum -= a[l++];
        }
    }
    printf("%d %d %d\n", ansl, ansr, anss);
    return 0;
}
