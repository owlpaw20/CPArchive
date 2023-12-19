#pragma GCC optimize("O2,unroll-loops")

#include <queue>
#include <string>
#include <cstring>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;
using PIS = pair<int, string>;
using PSC = pair<string, char>;

const int N = 3;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
const int dc[] = {'r', 'd', 'l', 'u'};

/* 每次移动只能把一个数字和空格交换位置
 * 这样至多把一个数字向它在目标状态中的位置移近一步
 * 即使每一步移动都是有意义的
 * 从任何一个状态到目标状态的移动步数
 * 也不可能小于所有数字当前位置与目标位置的曼哈顿距离之和
 * 所以用这个和作为每个状态的估价函数值 */

int eval(string s) {
    int ret = 0;
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] != 'x') {
            int t = s[i] - '1';
            ret += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }
    return ret;
}

string BFS(string st, string ed = "12345678x") {
    unordered_map<string, int> dist;
    unordered_map<string, PSC> prev;
    priority_queue<PIS, vector<PIS>, greater<PIS>> heap;

    dist[st] = 0;
    heap.emplace(eval(st), st);

    while (!heap.empty()) {
        string now = heap.top().second;
        heap.pop();

        if (now == ed) break;

        int dst = dist[now];
        int pos = now.find('x');
        int x = pos / 3, y = pos % 3;

        string src = now;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if (tx < 0 || ty < 0 || tx >= N || ty >= N) continue;

            swap(now[x * 3 + y], now[tx * 3 + ty]);
            if (!dist.count(now) || dist[now] > dst + 1) {
                dist[now] = dst + 1;
                prev[now] = PSC(src, dc[i]);
                heap.emplace(dist[now] + eval(now), now);
            }
            swap(now[x * 3 + y], now[tx * 3 + ty]);
        }
    }

    string ret;
    while (ed != st) {
        ret += prev[ed].second;
        ed = prev[ed].first;
    }
    return string(ret.rbegin(), ret.rend());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char c;
    string st, sq;
    while (cin >> c)
        st += c, sq = (c == 'x' ? sq : sq + c);

    int inv = 0;
    for (int i = 0; i < (int)sq.size(); i++)
        for (int j = i + 1; j < (int)sq.size(); j++)
            if (sq[i] > sq[j])
                inv += 1;

    if (inv & 1) return puts("unsolvable"), 0;
    cout << BFS(st) << endl;

    fflush(stdout);
    return 0;
}
