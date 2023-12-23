#include <bitset>
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 110;

int n;
bitset<N> cls[N];

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        f = ch != '-';
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return f ? x : -x;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cls[i][j] = read();
    for (int j = 1; j <= n; j++)
        for (int i = 1; i <= n; i++)
            if (cls[i][j])
                cls[i] |= cls[j];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            putchar(cls[i][j] + '0'), putchar(' ');
        putchar('\n');
    }
    return 0;
}
