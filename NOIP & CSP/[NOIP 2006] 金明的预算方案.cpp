#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 70;
const int M = 3.2e4 + 10;

int n, m;
int f[M];
PII major[N];
vector<PII> ext[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    for (int i = 1; i <= n; i++) {
        int v, p, q;
        cin >> v >> p >> q;
        p *= v;
        if (q == 0) major[i] = {v, p};
        else ext[q].emplace_back(v, p);
    }

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k < (1 << ext[i].size()); k++) {
                int v = major[i].first, w = major[i].second;
                for (int l = 0; l < ext[i].size(); l++)
                    if ((k >> l) & 1)
                        v += ext[i][l].first, w += ext[i][l].second;
                if (j >= v)
                    f[j] = max(f[j], f[j - v] + w);
            }

    cout << f[m] << endl;
    fflush(stdout);
    return 0;
}
