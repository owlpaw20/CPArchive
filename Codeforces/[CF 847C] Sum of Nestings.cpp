#include <iostream>
using namespace std;
using lng = long long;

lng n, k;

// 有 N 对括号尚需输出，K 层嵌套尚待构造
void nest(lng n, lng k) {
    if (n == 0)
        return;

    if (k < n - 1) {   // 如果需要嵌套的括号数量不支持再往内套一层
        putchar('(');  // 就在同层级继续套
        putchar(')');
        nest(n - 1, k);
    } else {           // 如果需要嵌套的括号大于往内套一层所能产生的贡献
        putchar('(');  // 就往内部套
        nest(n - 1, k - (n - 1));
        putchar(')');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    if (k > n * (n - 1) / 2)
        return puts("Impossible") && 0;

    nest(n, k);
    putchar('\n');
    return 0;
}
