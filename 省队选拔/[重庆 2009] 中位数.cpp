#include <iostream>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;

int n, b, a[N], flag[2 * N], p[2 * N];
int mid, cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> b;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == b)
            mid = i;
        else if (a[i] > b)
            flag[i] = 1;
        else if (a[i] < b)
            flag[i] = -1;
    }

    int sum = 0;
    for (int i = mid - 1; i > 0; i--) {
        sum += flag[i];
        p[sum + N]++;
        if (sum == 0) cnt++;
    }

    sum = 0;
    for (int i = mid + 1; i <= n; i++) {
        sum += flag[i];
        cnt += p[-sum + N];
        if (sum == 0) cnt++;
    }

    cout << ++cnt << endl;
    fflush(stdout);
    return 0;
}
