#include <string>
#include <cstring>
#include <iostream>

#define endl '\n'

using namespace std;

int n, m;
int cnt[26][2], ans[26];
// cnt[x][0]表示字母为(x+'A')的元素在等号左边的出现次数
// cnt[x][1]表示字母为(x+'A')的元素在等号右边的出现次数
// ans[x]表示问号代表的物质中各元素的化学计量数

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    while (n--) {
        memset(cnt, 0, sizeof cnt);
        memset(ans, 0, sizeof ans);  // 多测清空
        cin >> s;

        int len = s.size();
        bool equality = false;  // 是否已经找到等号
        int question_mark = 0;  // 问号的位置，1表示等号左边，2表示等号右边

        for (int i = 0; i < len; i++) {
            char now = s[i];
            char nxt = s[i + 1];
            if (isdigit(now)) {
                continue;
            } else if (now == '+') {
                continue;
            } else if (now == '?') {
                if (!equality) question_mark = 1;
                else question_mark = 2;
            } else if (now == '=') {
                equality = true;
            } else if (isalpha(now)) {
                if (!equality) {                       // 等号左边
                    int order_of_element = now - 'A';  // 取得元素对应的数组下标
                    int chemical_number = 1;           // 化学计量数初始化为1
                    if (isdigit(nxt))
                        chemical_number = nxt - '0';  // 如果字母跟了数字就当成化学计量数
                    cnt[order_of_element][0] += chemical_number;
                } else {  // 等号右边同理
                    int order_of_element = now - 'A';
                    int chemical_number = 1;
                    if (isdigit(nxt))
                        chemical_number = nxt - '0';
                    cnt[order_of_element][1] += chemical_number;
                }
            }
        }

        if (question_mark == 1)  // 问号在左边
            for (int i = 0; i < 26; i++)
                ans[i] = cnt[i][1] - cnt[i][0];  // 说明右边元素及其数量更多
        else if (question_mark == 2)             // 问号在右边
            for (int i = 0; i < 26; i++)
                ans[i] = cnt[i][0] - cnt[i][1];  // 说明左边元素及其数量更多
        
        bool valid = true;
        int empty_cnt = 0;

        for (int i = 0; i < 26; i++) {
            if (ans[i] < 0) valid = false;
            if (ans[i] > 9) valid = false;
            if (ans[i] == 0) empty_cnt++;  // 判断有多少个化学计量数为0的元素，用于判断无解情况
            if (!valid) break;
        }

        if (!valid || empty_cnt == 26)
            cout << "No Solution" << endl;
        else {
            for (int i = 0; i < 26; i++) {  // 按最简形式输出
                if (ans[i] == 0) continue;
                if (ans[i] == 1) cout << (char)(i + 'A');
                if (ans[i] >= 2) cout << (char)(i + 'A') << ans[i];
            }
            cout << endl;
        }
    }

    fflush(stdout);
    return 0;
}
