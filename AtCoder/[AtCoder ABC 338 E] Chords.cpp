#include <stack>
#include <iostream>

#define endl '\n'

using namespace std;

const int N = 4e5 + 5;

int n;
int vis[N];
stack<int> pt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1, x, y; i <= n; i++)
        cin >> x >> y, vis[x] = vis[y] = i;

    for (int i = 1; i <= n * 2; i++)
        if (pt.empty() || pt.top() != vis[i]) pt.push(vis[i]);
        else pt.pop();

    if (!pt.empty()) puts("Yes");
    else puts("No");

    return fflush(stdout), 0;
}
