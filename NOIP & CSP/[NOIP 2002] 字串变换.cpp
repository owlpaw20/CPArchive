#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;
using str = string;
using DICT = vector<str>;
using HASH = unordered_map<str, int>;

string C, D, a, b;
vector<str> ci, de;

int process(queue<str> &q, HASH &d_st, HASH &d_ed, DICT &fr, DICT &to) {
    int depth = d_st[q.front()];
    while (!q.empty() && d_st[q.front()] == depth) {
        string t = q.front();
        q.pop();

        for (int i = 0; i < (int)fr.size(); i++)
            for (int j = 0; j < (int)t.size(); j++)
                if (t.substr(j, fr[i].size()) == fr[i]) {
                    string x = t;
                    x.replace(j, fr[i].size(), to[i]);

                    if (d_ed.count(x)) return d_st[t] + d_ed[x] + 1;
                    if (d_st.count(x)) continue;

                    d_st[x] = d_st[t] + 1;
                    q.push(x);
                }
    }

    return -1;
}

int BFS() {
    if (C == D) return 0;

    queue<str> q_C, q_D;
    HASH dist_C, dist_D;
    q_C.push(C), q_D.push(D);
    dist_C[C] = dist_D[D] = 0;

    int depth = 0;
    while (!q_C.empty() && !q_D.empty()) {
        int ret = -1;
        if (q_C.size() < q_D.size())
            ret = process(q_C, dist_C, dist_D, ci, de);
        else
            ret = process(q_D, dist_D, dist_C, de, ci);

        if (ret != -1)
            return ret;
        if (++depth >= 10)
            return -1;
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> C >> D;
    while (cin >> a >> b)
        ci.push_back(a), de.push_back(b);

    int ret = BFS();
    if (ret == -1)
        puts("NO ANSWER!");
    else
        cout << ret << endl;

    fflush(stdout);
    return 0;
}
