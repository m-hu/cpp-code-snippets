/**
 * problem reference: https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid/
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * @class adj_iterator
 * @brief the iterator to get valid neighbor, inspired by Python generator;
 * another variant is the version where the iterator does the whole thing by generating the node to visit
 * directly in the DFS order
 *
 */
class adj_iterator {
 private:
  vector<vector<int> > &grid;
  int row;
  int col;
  int i;
  int j;
  adj_iterator& next(bool skip_current) {
    int nb_row = static_cast<int>(grid.size());
    int nb_col = static_cast<int>(grid[0].size());
    int x = row + i;
    int y = col + j;
    if (!skip_current) {
      if (x >= 0 && x < nb_row && y >= 0 && y < nb_col && grid[x][y] == 1)
        return *this;
    }
    do {
      if (i > 1) {
        break;
      } else {
        if (j < 1) {
          ++j;
        } else {
          ++i;
          j = -1;
        }
      }
      x = row + i;
      y = col + j;
    } while (!(x >= 0 && x < nb_row && y >= 0 && y < nb_col && grid[x][y] == 1));
    return *this;
  }
 public:
  adj_iterator(vector<vector<int> > &g, int r, int c)
      :
      grid(g),
      row(r),
      col(c),
      i(-1),
      j(-1) {
    next(false);
  }
  adj_iterator(vector<vector<int> > &g, int r, int c, int a, int b)
      :
      grid(g),
      row(r),
      col(c),
      i(a),
      j(b) {
    next(false);
  }
  adj_iterator(const adj_iterator &rhs)
      :
      grid(rhs.grid),
      row(rhs.row),
      col(rhs.col),
      i(rhs.i),
      j(rhs.j) {
    next(false);
  }
  adj_iterator& operator++() {
    return next(true);
  }
  adj_iterator operator++(int) {
    adj_iterator tmp(*this);
    operator++();
    return tmp;
  }
  bool operator==(const adj_iterator &rhs) const {
    return grid == rhs.grid && row == rhs.row && col == rhs.col && i == rhs.i
        && j == rhs.j;
  }
  bool operator!=(const adj_iterator &rhs) const {
    return !(grid == rhs.grid && row == rhs.row && col == rhs.col && i == rhs.i
        && j == rhs.j);
  }
  pair<int, int> operator*() {
    return {row + i, col + j};
  }
  adj_iterator end() {
    return adj_iterator(this->grid, this->row, this->col, 2, -1);
  }
};

int measure_region(vector<vector<int>> &grid, int row, int col) {
  int size = 1;
  grid[row][col] = -1;
  for (adj_iterator it(grid, row, col); it != it.end(); ++it) {
    int x, y;
    std::tie(x, y) = *it;
    if (grid[x][y] == 1)
      size += measure_region(grid, x, y);
  }
  return size;
}

// Complete the maxRegion function below.
int maxRegion(vector<vector<int>> grid) {
  int nb_row = static_cast<int>(grid.size());
  int nb_col = static_cast<int>(grid[0].size());
  int max_region = -1;
  for (int row = 0; row < nb_row; ++row) {
    for (int col = 0; col < nb_col; ++col) {
      if (grid[row][col] == 1) {
        int region_size = measure_region(grid, row, col);
        if (region_size > max_region)
          max_region = region_size;
      }
    }
  }
  return max_region;
}

int main() {
  int n;
  cin >> n;
  int m;
  cin >> m;
  vector<vector<int>> grid(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];
    }
  }
  int res = maxRegion(grid);
  cout << res << endl;
  return 0;
}
