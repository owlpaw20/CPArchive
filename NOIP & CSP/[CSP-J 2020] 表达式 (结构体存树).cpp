#include <cctype>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 1e6 + 10;

template <class Type>
struct stack {
  Type data[N];
  int t;
  void push(Type x) { data[++t] = x; }
  Type top() { return data[t]; }
  Type extract() { return data[t--]; }
  bool empty() { return !t; }
  stack() : t(0) {}
};

struct TreeNode {
  int l, r;
  void build(int tl) { l = tl; }
  void build(int tl, int tr) { l = tl, r = tr; }
};

string s;
int n, idx;
char opt[N];
stack<int> st;
TreeNode tr[N];
bool flag[N], var[N];

bool evaluate(int u) {
  if (u <= n) return var[u];
  if (opt[u] == '!') return var[u] = !evaluate(tr[u].l);
  if (opt[u] == '&') return var[u] = evaluate(tr[u].l) & evaluate(tr[u].r);
  return var[u] = evaluate(tr[u].l) | evaluate(tr[u].r);
}

void vary(int u) {
  flag[u] = true;
  if (u <= n) return;
  if (opt[u] == '!') return vary(tr[u].l);
  if (opt[u] == '&') {
    int x = tr[u].l, y = tr[u].r;
    if (var[x]) vary(y);
    if (var[y]) vary(x);
    return;
  }
  int x = tr[u].l, y = tr[u].r;
  if (!var[x]) vary(y);
  if (!var[y]) vary(x);
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);

  getline(cin, s);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> var[i];

  int len = s.size(), m = n;
  for (int i = 0; i < len; i++) {
    if (s[i] == 'x') {
      int var_num = 0;
      while (isdigit(s[++i]))  // 加入变量
        var_num = var_num * 10 + s[i] - '0';
      st.push(var_num);
    } else if (s[i] == '!') {
      opt[++m] = s[i++];
      tr[m].build(st.extract());  // 建立单目运算符的子树
      st.push(m);
    } else if (s[i] == '&' or s[i] == '|') {
      opt[++m] = s[i++];
      tr[m].build(st.extract(), st.extract());  // 建立双目运算符的子树
      st.push(m);
    }
  }

  int root = st.top();
  bool expr_res = evaluate(root);

  vary(root);

  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    if (flag[x])
      cout << !expr_res << endl;
    else
      cout << expr_res << endl;
  }

  return 0;
}
