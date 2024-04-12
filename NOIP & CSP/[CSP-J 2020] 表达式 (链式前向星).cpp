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
    void push(Type x) {
        data[++t] = x;
    }
    Type top() {
        return data[t];
    }
    Type extract() {
        return data[t--];
    }
    bool empty() {
        return !t;
    }
    stack() :
        t(0) {}
};

string s;
int n, idx;
char opt[N];
stack<int> st;
bool flag[N], var[N];
int ed[N], nx[N], head[N];

void connect(int u, int v) {
    ed[idx] = v;
    nx[idx] = head[u];
    head[u] = idx++;
}

bool evaluate(int u) {
    // 如果当前节点为变量则直接返回值
    if (u <= n)
        return var[u];

    // 如果运算符为按位取反，则对子树的计算结果取反
    if (opt[u] == '!')
        return var[u] = !evaluate(ed[head[u]]);

    // 如果运算符为按位与，则对两个子树的计算结果取反
    if (opt[u] == '&') {
        var[u] = 1;
        for (int i = head[u]; ~i; i = nx[i])
            var[u] &= evaluate(ed[i]);
        return var[u];
    }

    // 如果运算符为按位或，则对两个子树的计算结果取或
    var[u] = 0;
    for (int i = head[u]; ~i; i = nx[i])
        var[u] |= evaluate(ed[i]);
    return var[u];
}

void vary(int u) {
    // 标记当前遍历的节点若遭修改，则结果也会修改
    flag[u] = true;

    // 如果遍历到变量则直接返回
    if (u <= n)
        return;

    // 如果当前运算符为按位取反
    // 则若其作用的变量被修改，直接影响到子树的计算结果
    if (opt[u] == '!')
        return vary(ed[head[u]]);

    // 如果当前运算符为按位与
    // 若其中一个变量为1，另一个变量的修改直接影响到子树的计算结果
    if (opt[u] == '&') {
        int x = ed[head[u]], y = ed[nx[head[u]]];
        if (var[x]) vary(y);
        if (var[y]) vary(x);
        return;
    }

    // 如果当前运算符为按位或
    // 若其中一个变量为0，另一个变量的修改直接影响到子树的计算结果
    int x = ed[head[u]], y = ed[nx[head[u]]];
    if (!var[x]) vary(y);
    if (!var[y]) vary(x);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    memset(head, -1, sizeof head);

    getline(cin, s);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> var[i];

    int len = s.size(), m = n;
    for (int i = 0; i < len; i++) {
        if (s[i] == 'x') {
            int var_num = 0;
            while (isdigit(s[++i]))
                var_num = var_num * 10 + s[i] - '0';
            st.push(var_num);
        } else if (s[i] == '!') {
            opt[++m] = s[i++];
            connect(m, st.extract());
            st.push(m);
        } else if (s[i] == '&' or s[i] == '|') {
            opt[++m] = s[i++];
            connect(m, st.extract());
            connect(m, st.extract());
            st.push(m);
        }
    }

    int root = st.top();
    bool expr_res = evaluate(root);

    vary(root);  // 判断有哪些变量在修改后会导致结果被改变

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
