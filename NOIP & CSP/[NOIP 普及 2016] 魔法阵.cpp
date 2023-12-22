#include <iostream>

#define endl '\n'

using namespace std;

const int N = 2e4 + 10;
const int M = 4e4 + 10;

int n, m;
int x[M], cnt[N];
int a[N], b[N], c[N], d[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> x[i];
        cnt[x[i]]++;
    }

    for (int i = 1; i <= (n - 1) / 9; i++) {
        int sum = 0;
        for (int j = 9 * i + 2; j <= n; j++) {
            int A = j - 9 * i - 1;
            int B = j - 7 * i - 1;
            int C = j - i;
            sum += cnt[A] * cnt[B];
            c[C] += cnt[j] * sum;
            d[j] += cnt[C] * sum;
        }
        sum = 0;
        for (int j = n - 9 * i - 1; j >= 1; j--) {
            int B = j + 2 * i;
            int C = 8 * i + 1 + j;
            int D = 9 * i + 1 + j;
            sum += cnt[C] * cnt[D];
            a[j] += cnt[B] * sum;
            b[B] += cnt[j] * sum;
        }
    }

    for (int i = 1; i <= m; i++)
        printf("%d %d %d %d\n", a[x[i]], b[x[i]], c[x[i]], d[x[i]]);

    fflush(stdout);
    return 0;
}
