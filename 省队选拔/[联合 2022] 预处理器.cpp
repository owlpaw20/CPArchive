#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

#define endl '\n'

using namespace std;
using PSB = pair<string, bool>;

int n;
string tmp;
unordered_map<string, PSB> macro;

bool check(char ch) {
  return isalnum(ch) || ch == '_';
}

string expand(string s) {
  string ret;

  int len = s.length();

  for (int i = 0, j = 0; i < len; i += j) {
    j = 0;
    while (i + j < len && check(s[i + j])) j++;

    if (j != 0) {
      string ss = s.substr(i, j);
      if (macro.count(ss) && !macro[ss].second) {
        macro[ss].second = true;
        ret += expand(macro[ss].first);
        macro[ss].second = false;
      } else
        ret += ss;
    } else
      ret += s[i++];
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  getline(cin, tmp);

  while (n--) {
    string expr;
    getline(cin, expr);

    if (expr.substr(0, 7) == "#define") {
      int second_space = expr.find_first_of(" \n", 8);
      string macro_name = expr.substr(8, second_space - 8);
      string macro_content = expr.substr(second_space + 1);

      macro[macro_name] = PSB(macro_content, false);

      cout << endl;
      continue;
    }

    if (expr.substr(0, 6) == "#undef") {
      string macro_name = expr.substr(7);

      if (macro.count(macro_name))
        macro.erase(macro_name);

      cout << endl;
      continue;
    }

    cout << expand(expr) << endl;
  }

  fflush(stdout);
  return 0;
}
