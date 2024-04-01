#include <queue>
#include <string>
#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;
using std::string;

int N;
string S, T;
std::queue<int> q;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> S >> T;

    if (S == T) return cout << 0 << endl, 0;

    int l = N - 1, r = N - 1;
    int ans = 0;

    while (r >= 0) {
        while (r && T[r - 1] == T[r]) --r;
        while (l >= 0 && (l > r || S[l] != T[r])) --l;

        if (l < 0) return cout << -1 << endl, 0;

        while (!q.empty() && q.front() - (int)q.size() >= r) q.pop();
        if (l != r) q.push(l);

        ans = std::max(ans, (int)q.size() + 1);
        --r;
    }

    cout << ans << endl;

    return fflush(stdout), 0;
}
