#pragma GCC optimize("O2,unroll-loops,inline")

#include <map>
#include <set>
#include <tuple>
#include <string>
#include <iostream>

using PCC = std::pair<char, char>;
using TUP = std::tuple<int, int, bool>;

using std::get;

const int MAX_N = 1e2 + 5;
const int MAX_P = 11;
const PCC QUAFFLE = PCC('.', 'Q');
const PCC BLUDGER = PCC('.', 'B');
const PCC SNITCH = PCC('.', 'S');
const PCC VOID = PCC('.', '.');

int N, M, R, B, t;
std::map<PCC, TUP> player;
std::set<PCC> map[MAX_N][MAX_N];
char goals[MAX_N][MAX_N];
int bx, by;

void check_goal(int x, int y) {
  if (!goals[x][y]) return;
  std::cout << t << (goals[x][y] == 'R' ? " BLUE GOAL\n" : " RED GOAL\n");
  goals[x][y] == 'R' ? ++B : ++R;
}

void check_elimination() {
  if (map[bx][by].empty()) return;
  for (PCC x : map[bx][by])
    if (x != BLUDGER)
      std::cout << t << ' ' << x.first << x.second << " ELIMINATED\n";
  map[bx][by].clear();
  map[bx][by].insert(BLUDGER);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;

  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j) {
      char a, b;
      std::cin >> a >> b;

      PCC entity(a, b);

      if (a == 'R')
        if (isdigit(b)) player.emplace(entity, TUP(i, j, true));
        else goals[i][j] = a;
      else if (a == 'B')
        if (isdigit(b)) player.emplace(entity, TUP(i, j, true));
        else goals[i][j] = a;
      else if (entity == BLUDGER)
        bx = i, by = j;

      if (entity != VOID && entity != QUAFFLE && entity != SNITCH)
        map[i][j].emplace(a, b);
    }

  int T;
  std::cin >> T;
  for (t = 0; t < T; ++t) {
    char a, b, type;
    std::cin >> a >> b >> type;

    PCC entity(a, b);
    PCC is_golden_snitch_caught = VOID;

    if (entity == BLUDGER) {
      if (type == 'U') map[bx][by].erase(BLUDGER), map[--bx][by].insert(BLUDGER);
      else if (type == 'D') map[bx][by].erase(BLUDGER), map[++bx][by].insert(BLUDGER);
      else if (type == 'L') map[bx][by].erase(BLUDGER), map[bx][--by].insert(BLUDGER);
      else if (type == 'R') map[bx][by].erase(BLUDGER), map[bx][++by].insert(BLUDGER);
    } else {
      auto& [x, y, k] = player[entity];
      if (type == 'U') map[x][y].erase(entity), map[--x][y].insert(entity);
      else if (type == 'D') map[x][y].erase(entity), map[++x][y].insert(entity);
      else if (type == 'L') map[x][y].erase(entity), map[x][--y].insert(entity);
      else if (type == 'R') map[x][y].erase(entity), map[x][++y].insert(entity);
      else if (type == 'T') check_goal(x, y);
      else {
        std::cin >> a >> b;
        if (PCC(a, b) == SNITCH) is_golden_snitch_caught = entity;
      }
    }

    check_elimination();

    if (is_golden_snitch_caught != VOID && get<2>(player[entity])) {
      std::cout << t << (is_golden_snitch_caught.first == 'R' ? " RED" : " BLUE") << " CATCH GOLDEN SNITCH\n";
      is_golden_snitch_caught.first == 'R' ? R += 10 : B += 10;
      break;
    }
  }

  std::cout << "FINAL SCORE: " << R << ' ' << B << std::endl;
  return 0;
}
