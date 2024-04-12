#include <iostream>
#define ti first
#define na second
using namespace std;
using PII = pair<int, int>;

const int N = 300000 + 5;
const int LMT = 86400;

template <class Type>
struct queue {
    Type data[N];
    int head, rear;
    void push(Type x) {
        data[++rear] = x;
    }
    void pop() {
        head++;
    }
    Type front() {
        return data[head];
    }
    Type back() {
        return data[rear];
    }
    bool empty() {
        return head > rear;
    }
    int size() {
        return rear - head + 1;
    }
    queue() :
        head(0), rear(-1) {}
};

int n, ans;
int vis[N];
queue<PII> q;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    while (n--) {
        int t, p;
        cin >> t >> p;
        while (!q.empty() && t - q.front().ti >= LMT) {
            vis[q.front().na]--;
            if (vis[q.front().na] == 0) ans--;
            q.pop();
        }
        while (p--) {
            int k;
            cin >> k;
            if (vis[k] == 0) ans++;
            vis[k]++;
            q.push({t, k});
        }
        cout << ans << endl;
    }
    return 0;
}
