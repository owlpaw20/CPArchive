#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;
using lng = long long;

const int N = 2e6 + 10;

template <class Type>
class Stack {
  private:
    vector<Type> data;

  public:
    Stack() {}
    Stack(int n) { data.reserve(n); }
    int size() const { return data.size(); }
    void push(const Type x) { data.push_back(x); }
    void pop() { data.pop_back(); }
    bool empty() { return data.empty(); }
    const Type top() { return data.back(); }
    const Type operator[](const int idx) const { return data[idx]; }
    const Type extract() {
        Type t = data.back();
        data.pop_back();
        return t;
    }
};

using STK = Stack<char>;

class Trie {
  private:
    int tr[N][26];
    int cnt[N];
    int idx;

  public:
    void insert(const STK& st) {
        int p = 0, len = st.size();
        for (int i = 0; i < len; i++) {
            int c = st[i] - 'a';
            if (!tr[p][c])
                tr[p][c] = ++idx;
            p = tr[p][c];
        }
        cnt[p]++;
    }

    int find(const STK& st) const {
        int p = 0, len = st.size();
        for (int i = 0; i < len; i++) {
            int c = st[i] - 'a';
            if (!tr[p][c])
                return 0;
            p = tr[p][c];
        }
        return cnt[p];
    }

    Trie() : idx(0) {
        memset(tr, 0, sizeof tr);
        memset(cnt, 0, sizeof cnt);
    }
};

int n;
Trie tr;
string s;
STK st(N);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    lng ans = 0;
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (!st.empty() && st.top() == s[i]) {
            st.pop();
            if (st.empty()) ans++;
        } else
            st.push(s[i]);

        ans += tr.find(st);
        tr.insert(st);
    }

    cout << ans << endl;
    return 0;
}
