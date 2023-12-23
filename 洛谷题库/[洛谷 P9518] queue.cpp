#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;
using PSI = pair<string, int>;

const int N = 1e5 + 10;

int n, idx;
string s, t;

unordered_map<string, int> status;
unordered_map<string, int> latest;

// 0 = left
// 1 = queued
// 2 = playing

struct Queue {
    PSI name[N];
    int head = 0, tail = -1;
    int size() { return tail - head + 1; }
    PSI front() { return name[head]; }
    PSI back() { return name[tail]; }
    bool empty() { return head > tail; }
    void push(string s) { name[++tail] = {s, latest[s]}; }
    void pop() { head++; }
    void clean_up() {
        while ((status[front().first] == 0 || front().second != latest[front().first]) && !empty())
            pop();
    }
} q, occupied;

string game_start() {
    while (occupied.size()) {
        string s = occupied.front().first;
        occupied.pop();
        status[s] = 1;
        q.push(s);
    }
    q.clean_up();
    if (q.empty()) return "Error";
    string player1 = q.front().first;
    q.pop();
    status[player1] = 2;
    occupied.push(player1);
    q.clean_up();
    if (q.empty()) return player1;
    string player2 = q.front().first;
    q.pop();
    status[player2] = 2;
    occupied.push(player2);
    return player1 + " " + player2;
}

string arrival(string s) {
    if (status[s] != 0) return "Error";
    latest[s] = ++idx;
    q.push(s);
    status[s] = 1;
    return "OK";
}

string leaving(string s) {
    if (status[s] != 1) return "Error";
    status[s] = 0;
    return "OK";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    while (n--) {
        cin >> s;
        if (s == "start") {
            cout << game_start() << endl;
        } else if (s == "arrive") {
            cin >> t;
            cout << arrival(t) << endl;
        } else if (s == "leave") {
            cin >> t;
            cout << leaving(t) << endl;
        }
    }
    return 0;
}
