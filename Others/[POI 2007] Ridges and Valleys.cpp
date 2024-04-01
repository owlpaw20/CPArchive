#include <vector>
#include <iostream>
using namespace std;
using PII = pair<int, int>;

const int N = 1e3 + 10;
const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[] = {-1, -1, 0, 1, 1, -1, 0, 1};

template <class T>
struct queue {
    vector<T> data;
    int head, rear;
    void push(T x) {
        data[++rear] = x;
    }
    void pop() {
        head++;
    }
    T extract() {
        return data[head++];
    }
    T front() {
        return data[head];
    }
    T back() {
        return data[rear];
    }
    bool empty() {
        return head > rear;
    }
    queue(int n) : head(0), rear(-1) {
        data.resize(n + 10);
    }
};

int n;
int mat[N][N];
bool vis[N][N];
queue<PII> q(1e6 + 10);

void BFS(int sx, int sy, bool& hi, bool& lo) {
    vis[sx][sy] = true;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.extract();
        for (int i = 0; i < 8; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
            if (mat[tx][ty] > mat[x][y]) hi = true;
            else if (mat[tx][ty] < mat[x][y]) lo = true;
            else if (!vis[tx][ty]) {
                vis[tx][ty] = true;
                q.push({tx, ty});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> mat[i][j];

    int peak = 0, valley = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!vis[i][j]) {
                bool hi = false, lo = false;
                BFS(i, j, hi, lo);
                if (!hi) peak++;
                if (!lo) valley++;
            }

    cout << peak << " " << valley << endl;
    return 0;
}
