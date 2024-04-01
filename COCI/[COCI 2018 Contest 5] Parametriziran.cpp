#include <iostream>
#include <unordered_map>
using namespace std;
using i64 = long long;

const int P = 31;

int n, m;
i64 ans;
char s[10];
unordered_map<int, int> mp;

void insert(char* s, int i, int k) {
    if (i == m) {
        mp[k] += 1;
        return;
    }
    int mul = k * P;
    if (s[i] != '?') {
        insert(s, i + 1, mul + s[i] - 'a');
        insert(s, i + 1, mul + 26);
    } else
        insert(s, i + 1, mul + 27);
}

int query(char* s, int i, int k) {
    if (i == m) {
        if (mp.count(k))
            return mp[k];
        return 0;
    }
    int ret = 0, mul = k * P;
    if (s[i] != '?')
        ret += query(s, i + 1, mul + s[i] - 'a');
    else
        ret += query(s, i + 1, mul + 26);
    ret += query(s, i + 1, mul + 27);
    return ret;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m;
    while (n--) {
        cin >> s;
        ans += query(s, 0, 0);
        insert(s, 0, 0);
    }
    cout << ans << endl;
    return 0;
}
