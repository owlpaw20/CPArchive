#include <string>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

string s, a[N];
int n, m, tot, ans1, ans2;
unordered_map<string, int> p;
unordered_map<string, bool> flag;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s, flag[s] = true;

    cin >> m;

    int l = 1;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        if (flag[a[i]]) p[a[i]]++;
        if (p[a[i]] == 1) ans1++, ans2 = i - l + 1;
        while (l <= i)
            if (!flag[a[l]])
                l++;
            else if (p[a[l]] > 1)
                p[a[l]]--, l++;
            else
                break;
        ans2 = min(ans2, i - l + 1);
    }

    cout << ans1 << endl;
    cout << ans2 << endl;
    fflush(stdout);
    return 0;
}
