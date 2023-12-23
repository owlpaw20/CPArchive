#include <vector>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using lng = long long;
using PriorityQueue = __gnu_pbds::priority_queue<int, greater<int>>;

int n, T;
vector<int> d;
PriorityQueue heap;

bool check(lng x) {
    heap.clear();
    for (int i = 0; i < n; i++)
        if (i + 1 <= x)
            heap.push(d[i]);
        else {
            heap.push(heap.top() + d[i]);
            heap.pop();
        }
    int time = 0;
    while (!heap.empty()) {
        time = heap.top();
        heap.pop();
        if (time > T)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> T;
    d.resize(n);
    for (int i = 0; i < n; i++)
        cin >> d[i];

    lng l = 1, r = 1e10;
    while (l < r) {
        lng mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    cout << r << endl;
    return 0;
}
