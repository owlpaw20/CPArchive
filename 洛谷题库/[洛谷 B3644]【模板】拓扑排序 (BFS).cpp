#include <queue>
#include <vector>
#include <iostream>

#define endl '\n'

using namespace std;

int n;
vector<int> in;
vector<vector<int>> edges;

vector<int> topological_sort(int n) {
    queue<int> q;
    vector<int> seq;

    for (int u = 1; u <= n; u++)
        if (in[u] == 0)
            q.push(u);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        seq.push_back(u);

        for (int v : edges[u])
            if (--in[v] == 0)
                q.push(v);
    }

    return seq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    in.resize(n + 1);
    edges.resize(n + 1);

    for (int u = 1, v; u <= n; u++)
        while (cin >> v, v)
            edges[u].push_back(v), in[v]++;

    vector<int> seq = topological_sort(n);

    for (int u : seq)
        cout << u << ' ';

    cout << endl;
    fflush(stdout);
    return 0;
}
