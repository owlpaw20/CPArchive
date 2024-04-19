#include <iostream>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define endl '\n'

using PII = std::pair<int, int>;

__gnu_pbds::tree<PII, __gnu_pbds::null_type, std::greater<PII>,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>
  tree_1, tree_2;

int n, least;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> least;

  int changes = 0, ans = 0;

  while (n--) {
    char x;
    int k;

    std::cin >> x >> k;

    if (x == 'I') {
      k += changes;
      if (k >= least) tree_1.insert(PII(k, n));
    } else if (x == 'A') {
      least -= k;
      changes -= k;
    } else if (x == 'S') {
      least += k;
      changes += k;
      tree_1.split(PII(least, -1), tree_2);
      ans += tree_2.size();
    } else {
      if (k > (int)tree_1.size()) std::cout << -1 << endl;
      else std::cout << tree_1.find_by_order(k - 1)->first - changes << '\n';
    }
  }

  std::cout << ans << endl;
  return fflush(stdout), 0;
}
