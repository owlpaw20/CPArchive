#include <cmath>
#include <limits>
#include <iostream>
#include <algorithm>

#define endl '\n'

using std::cin;
using std::cout;

using f64 = double;
using PFF = std::pair<f64, f64>;

const int MAX_N = 4e5 + 5;

int N;
PFF pt[MAX_N], tmp[MAX_N];

auto dist = [](const PFF x, const PFF y) -> f64 {
    const f64 xd = x.first - y.first;
    const f64 yd = x.second - y.second;
    return sqrt(xd * xd + yd * yd);
};

f64 DAC(const int l, const int r) {
    if (l == r) return std::numeric_limits<long long>::max();
    if (l + 1 == r) return dist(pt[l], pt[r]);

    const int mid = (l + r) >> 1;
    f64 ret = std::min(DAC(l, mid), DAC(mid + 1, r));

    int cnt = 0;

    for (int i = l; i <= r; ++i)
        if (fabs(pt[mid].first - pt[i].first) < ret)
            tmp[cnt++] = pt[i];

    std::sort(tmp, tmp + cnt, [&](PFF a, PFF b) {
        return a.second < b.second;
    });

    for (int i = 0; i < cnt; ++i)
        for (int j = i + 1; j < cnt; ++j)
            if (tmp[j].second - tmp[i].second < ret)
                ret = std::min(ret, dist(tmp[i], tmp[j]));
            else
                break;

    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> pt[i].first >> pt[i].second;

    std::sort(pt, pt + N);

    f64 ret = DAC(0, N - 1);

    cout << (long long)round(ret * ret) << endl;
    return fflush(stdout), 0;
}
