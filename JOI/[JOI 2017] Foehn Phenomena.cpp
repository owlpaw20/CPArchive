#include <iostream>

#define endl '\n'

using std::cin;
using std::cout;

using i64 = long long;

const int MAX_N = 2e5 + 5;

int N, Q, S, T;
i64 delta[MAX_N];

i64 alter(i64 i) {
    if (delta[i] > 0) return -delta[i] * S;
    return -delta[i] * T;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int last = 0;
    i64 ans = 0;

    cin >> N >> Q >> S >> T >> last;

    for (int i = 1, curr; i <= N; i++) {
        cin >> curr;
        delta[i] = curr - last;
        ans += alter(i);
        last = curr;
    }

    while (Q--) {
        int L, R, X;
        cin >> L >> R >> X;

        ans -= alter(L);
        delta[L] += X;
        ans += alter(L);

        if (R < N) {
            ans -= alter(R + 1);
            delta[R + 1] -= X;
            ans += alter(R + 1);
        }

        cout << ans << endl;
    }

    return fflush(stdout), 0;
}
