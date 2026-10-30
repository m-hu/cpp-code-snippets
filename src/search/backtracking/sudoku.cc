/*
 * https://www.hackerrank.com/challenges/sudoku/problem
 */
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

class SudokuSolver {
 private:
  int map[9][9];
  // Bit d (1..9) set means digit d is already used in that unit.
  unsigned rows[9];
  unsigned cols[9];
  unsigned boxes[9];

  static int box_id(int row, int col) {
    return (row / 3) * 3 + col / 3;
  }

  void clear_board() {
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        map[row][col] = 0;
      }
    }
    memset(rows, 0, sizeof(rows));
    memset(cols, 0, sizeof(cols));
    memset(boxes, 0, sizeof(boxes));
  }

 public:
  SudokuSolver() {
    clear_board();
  }

  void load_board() {
    clear_board();
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        cin >> map[i][j];
        if (map[i][j] != 0) {
          unsigned bit = 1u << map[i][j];
          rows[i] |= bit;
          cols[j] |= bit;
          boxes[box_id(i, j)] |= bit;
        }
      }
    }
  }

  // Minimum-remaining-values search: always branch on the empty cell
  // with the fewest legal digits (first such cell in row-major order,
  // digits tried ascending). The previous row-major cell order found
  // a different valid completion than the stored expected outputs on
  // most shared cases whenever a puzzle admitted several completions;
  // this selection is the one the Go mirror (and the expected outputs)
  // use.
  bool solve() {
    int best_row = -1, best_col = -1, best_count = 10;
    unsigned best_mask = 0;
    for (int r = 0; r < 9; r++) {
      for (int c = 0; c < 9; c++) {
        if (map[r][c] != 0) {
          continue;
        }
        unsigned used = rows[r] | cols[c] | boxes[box_id(r, c)];
        unsigned mask = 0;
        int count = 0;
        for (int d = 1; d <= 9; d++) {
          if (!(used & (1u << d))) {
            mask |= 1u << d;
            count++;
          }
        }
        if (count == 0) {
          return false;
        }
        if (count < best_count) {
          best_count = count;
          best_row = r;
          best_col = c;
          best_mask = mask;
          if (count == 1) {
            break;
          }
        }
      }
      if (best_count == 1) {
        break;
      }
    }
    if (best_row == -1) {
      return true;
    }
    int b = box_id(best_row, best_col);
    for (int d = 1; d <= 9; d++) {
      unsigned bit = 1u << d;
      if (!(best_mask & bit)) {
        continue;
      }
      map[best_row][best_col] = d;
      rows[best_row] |= bit;
      cols[best_col] |= bit;
      boxes[b] |= bit;
      if (solve()) {
        return true;
      }
      rows[best_row] &= ~bit;
      cols[best_col] &= ~bit;
      boxes[b] &= ~bit;
      map[best_row][best_col] = 0;
    }
    return false;
  }

  void print_board() {
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        cout << map[i][j] << " ";
      }
      cout << endl;
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  SudokuSolver solver;
  int i;
  rep(i, 0, n)
  {
    solver.load_board();
    solver.solve();
    solver.print_board();
  }
  return 0;
}
