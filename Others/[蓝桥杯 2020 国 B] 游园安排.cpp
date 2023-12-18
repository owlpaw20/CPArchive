#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define endl '\n'
using namespace std;

vector<string> s;
vector<string> f, ans;

void read() {
    char ch;
    string name;
    while (cin >> ch) {
        name += ch;
        if (isupper(cin.peek())) {
            s.push_back(name);
            name.clear();
        }
    }
    if (!name.empty())
        s.push_back(name);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read();
    f.resize(s.size() + 5);
    ans.resize(s.size() + 5);

    int used = 0;
    for (string str : s) {
        int l = 1, r = used + 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (f[mid] >= str) r = mid;
            else l = mid + 1;
        }
        f[r] = str;
        used = max(used, r);
        ans[r] = ans[r - 1] + str;
    }

    cout << ans[used] << endl;

    fflush(stdout);
    return 0;
}
