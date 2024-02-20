#include <string>
#include <iostream>

#define endl '\n'

using namespace std;

string s;
int vis[26];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    for (char ch : s)
        vis[ch - 'a']++;

    int maxvis = 0;
    char maxvischar = '\0';
    for (int i = 0; i < 26; i++)
        if (vis[i] > maxvis)
            maxvis = vis[i], maxvischar = i + 'a';

    cout << maxvischar << endl;
    return fflush(stdout), 0;
}
