#include <cmath>
#include <limits>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;
using std::vector;

using f64 = double;
using PFF = std::pair<f64, f64>;

int N;
vector<PFF> pt;

auto dist = [](const PFF x, const PFF y) {
    const f64 xd = x.first - y.first;
    const f64 yd = x.second - y.second;
    return sqrt(xd * xd + yd * yd);
};

f64 DAC(const int l, const int r) {
    if (l == r) return std::numeric_limits<int>::max();
    if (l + 1 == r) return dist(pt[l], pt[r]);

    const int mid = std::midpoint(l, r);
    f64 ret = std::min(DAC(l, mid), DAC(mid + 1, r));

    vector<PFF> tmp;

    for (int i = l; i <= r; ++i)
        if (fabs(pt[mid].first - pt[i].first) < ret)
            tmp.push_back(pt[i]);

    std::sort(tmp.begin(), tmp.end(), [&](PFF a, PFF b) {
        return a.second < b.second;
    });

    for (size_t i = 0; i < tmp.size(); ++i)
        for (size_t j = i + 1; j < tmp.size(); ++j)
            if (tmp[j].second - tmp[i].second < ret)
                ret = std::min(ret, dist(tmp[i], tmp[j]));

    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(4);

    cin >> N;
    pt.reserve(N + 5);
    for (int i = 1, x, y; i <= N; ++i) {
        cin >> x >> y;
        pt.emplace_back(x, y);
    }

    std::sort(pt.begin(), pt.end());

    cout << std::fixed << DAC(0, N - 1) << endl;
    return fflush(stdout), 0;
}
