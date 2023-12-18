#include <vector>
#include <iostream>

using namespace std;

const int N = 30;

int n, x, y;
string s1, s2;
vector<int> pile[N];

void block(int target, int& p, int& h) {
    for (p = 0; p < n; p++)
        for (h = 0; h < pile[p].size(); h++)
            if (pile[p][h] == target)
                return;
}

void reset(int p, int h) {
    for (int i = h + 1; i < pile[p].size(); i++)
        pile[pile[p][i]].emplace_back(pile[p][i]);
    pile[p].resize(h + 1);
}

void pile_onto(int p_from, int p_to, int h) {
    for (int i = h; i < pile[p_from].size(); i++)
        pile[p_to].emplace_back(pile[p_from][i]);
    pile[p_from].resize(h);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; i++)
        pile[i].emplace_back(i);

    while (1) {
        cin >> s1 >> x >> s2 >> y;
        if (s1 == "quit") break;
        int where_x, where_y, height_x, height_y;
        block(x, where_x, height_x);
        block(y, where_y, height_y);
        if (where_x == where_y) continue;
        if (s2 == "onto") reset(where_y, height_y);
        if (s1 == "move") reset(where_x, height_x);
        pile_onto(where_x, where_y, height_x);
    }

    for (int i = 0; i < n; i++) {
        cout << i << ":";
        for (int j : pile[i]) cout << " " << j;
        cout << endl;
    }

    return 0;
}
