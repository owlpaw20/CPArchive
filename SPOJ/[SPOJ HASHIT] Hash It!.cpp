#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const int N = 101;
const int MOD = 101;

struct HashTable {
  vector<string> tb;
  set<string> flg;
  void init() {
    tb.resize(N);
  }
  int hash(string s) {
    int len = s.length(), sum = 0;
    for (int i = 0; i < len; i++)
      sum += s[i] * (i + 1);
    return 19 * sum % MOD;
  }
  void insert(string s) {
    if (flg.count(s)) return;
    int addr = 0;
    for (int j = 0; j <= 19; j++) {
      addr = (hash(s) + j * j + 23 * j) % MOD;
      if (tb[addr].empty()) break;
    }
    if (!tb[addr].empty()) return;
    tb[addr] = s;
    flg.insert(s);
  }
  void remove(string s) {
    if (!flg.count(s)) return;
    int addr = 0;
    for (int j = 0; j <= 19; j++) {
      addr = (hash(s) + j * j + 23 * j) % MOD;
      if (tb[addr] == s) break;
    }
    if (tb[addr] != s) return;
    tb[addr] = "";
    flg.erase(s);
  }
  int size() {
    return flg.size();
  }
  void print() {
    cout << size() << endl;
    for (int i = 0; i < tb.size(); i++)
      if (tb[i] != "" && flg.count(tb[i]))
        cout << i << ":" << tb[i] << endl;
  }
  HashTable() {
    init();
  }
};

int T;

void solve() {
  int q;
  HashTable t;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;
    string opt = s.substr(0, 4);
    string str = s.substr(4, s.length() - 4);
    if (opt == "ADD:") t.insert(str);
    if (opt == "DEL:") t.remove(str);
  }
  t.print();
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> T;
  while (T--) solve();
  return 0;
}
