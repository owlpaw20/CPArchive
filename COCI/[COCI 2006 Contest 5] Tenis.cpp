#include <string>
#include <sstream>
#include <iostream>

#define endl '\n'

using namespace std;

const int LEN = 25;

int n;
int federer;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    cin >> A >> B;
    if (A == "federer") federer = 1;
    if (B == "federer") federer = 2;

    cin >> n;
    getline(cin, A);

    while (n--) {
        int round_held = 1;
        int a_have_won = 0;
        int b_have_won = 0;
        bool have_invalid = false;

        int a, b;
        char op;

        string ss;
        getline(cin, ss);
        stringstream ssin(ss);

        while (ssin >> a >> op >> b) {
            if (have_invalid) continue;
            if (round_held > 3) have_invalid = true;
            if (a < 6 && b < 6) have_invalid = true;
            if (a >= 6 && b >= 6 && abs(a - b) != 2) have_invalid = true;
            if (round_held < 3 && a >= 6 && a > b && a - b < 2) have_invalid = true;
            if (round_held < 3 && b >= 6 && b > a && b - a < 2) have_invalid = true;
            if (round_held < 3 && a == 7 && b == 6) have_invalid = false;
            if (round_held < 3 && b == 7 && a == 6) have_invalid = false;
            if (round_held == 3 && a >= 6 && a > b && a - b < 2) have_invalid = true;
            if (round_held == 3 && b >= 6 && b > a && b - a < 2) have_invalid = true;
            if (federer == 1 && a < b) have_invalid = true;
            if (federer == 2 && b < a) have_invalid = true;
            if (round_held == 3 && abs(a - b) < 2) have_invalid = true;
            if (round_held < 3 && (a > 7 || b > 7)) have_invalid = true;

            if (a > b) a_have_won++;
            else b_have_won++;

            if (a_have_won > 2) have_invalid = true;
            if (b_have_won > 2) have_invalid = true;

            round_held++;
        }

        if (a_have_won < 2 && b_have_won < 2) have_invalid = true;

        if (have_invalid) cout << "ne" << endl;
        else cout << "da" << endl;
    }

    return fflush(stdout), 0;
}
