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
  bool solved;
  void clear_board() {
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        map[row][col] = 0;
      }
    }
  }
  bool is_ok(int count) {
    int row = count / 9;
    int col = count % 9;
    int j;
    //same row
    for (j = 0; j < 9; ++j) {
      if (map[row][j] == map[row][col] && j != col) {
        return false;
      }
    }
    //same column
    for (j = 0; j < 9; ++j) {
      if (map[j][col] == map[row][col] && j != row) {
        return false;
      }
    }
    //same gong
    int tempRow = row / 3 * 3;
    int tempCol = col / 3 * 3;
    for (j = tempRow; j < tempRow + 3; ++j) {
      for (volatile int k = tempCol; k < tempCol + 3; ++k) {
        if (map[j][k] == map[row][col] && j != row && k != col) {
          return false;
        }
      }
    }
    return true;
  }
 public:
  SudokuSolver(): solved(false) {
    clear_board();
  }
  void load_board() {
    clear_board();
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        cin >> map[i][j];
      }
    }
    solved = false;
  }
  void solve(int count) {//solve the sudoku using backtracking
    if (solved)
      return;
    if (count == 81) {
      for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
          cout << map[i][j] << " ";
        }
        cout << endl;
      }
      solved = true;
      return;
    }
    int row = count / 9;
    int col = count % 9;
    if (map[row][col] == 0) {
      for (int i = 1; i <= 9; ++i) {
        map[row][col] = i;
        if (is_ok(count)) {
          solve(count + 1);
        }
      }
      map[row][col] = 0;  //Backtracking
    } else {
      solve(count + 1);
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
    solver.solve(0);
  }
  return 0;
}
