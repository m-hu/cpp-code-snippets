/*
 * https://www.hackerrank.com/challenges/sudoku/problem
 */
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
#define IT(i, A, x) for (i = A[x]; i != x; i = A[i])
const int N = 1e6 + 10;
const int MAXSIZE = 1e5 + 10;
using namespace std;

class DLXSolver
{
private:
  int ans[10][10];
  int stk[N];
  int n, m, tot, first[MAXSIZE + 10], siz[MAXSIZE + 10];
  int L[MAXSIZE + 10], R[MAXSIZE + 10], U[MAXSIZE + 10], D[MAXSIZE + 10];
  int col[MAXSIZE + 10], row[MAXSIZE + 10];
  int get_id(int r, int c, int num)
  {
    return (r - 1) * 9 * 9 + (c - 1) * 9 + num;
  }
  void _insert(int r, int c, int num)
  {
    int dx = (r - 1) / 3 + 1;
    int dy = (c - 1) / 3 + 1;
    int room = (dx - 1) * 3 + dy;
    int id = get_id(r, c, num);
    int f1 = (r - 1) * 9 + num;             // task 1
    int f2 = 81 + (c - 1) * 9 + num;        // task 2
    int f3 = 81 * 2 + (room - 1) * 9 + num; // task 3
    int f4 = 81 * 3 + (r - 1) * 9 + c;      // task 4
    this->insert(id, f1);
    this->insert(id, f2);
    this->insert(id, f3);
    this->insert(id, f4);
  }

public:
  void build(const int &r, const int &c)
  {
    n = r, m = c;
    for (int i = 0; i <= c; ++i)
    {
      L[i] = i - 1, R[i] = i + 1;
      U[i] = D[i] = i;
    }
    L[0] = c, R[c] = 0, tot = c;
    memset(first, 0, sizeof(first));
    memset(siz, 0, sizeof(siz));
  }
  void insert(const int &r, const int &c)
  {
    col[++tot] = c, row[tot] = r, ++siz[c];
    D[tot] = D[c], U[D[c]] = tot, U[tot] = c, D[c] = tot;
    if (!first[r])
      first[r] = L[tot] = R[tot] = tot;
    else
    {
      R[tot] = R[first[r]], L[R[first[r]]] = tot;
      L[tot] = first[r], R[first[r]] = tot;
    }
  }
  void remove(const int &c)
  {
    int i, j;
    L[R[c]] = L[c], R[L[c]] = R[c];
    IT(i, D, c)
    IT(j, R, i)
    U[D[j]] = U[j],
    D[U[j]] = D[j], --siz[col[j]];
  }
  void recover(const int &c)
  {
    int i, j;
    IT(i, U, c)
    IT(j, L, i)
    U[D[j]] = D[U[j]] = j,
    ++siz[col[j]];
    L[R[c]] = R[L[c]] = c;
  }
  bool dance(int dep)
  {
    int i, j, c = R[0];
    if (!R[0])
    {
      for (i = 1; i < dep; ++i)
      {
        int x = (stk[i] - 1) / 9 / 9 + 1;
        int y = (stk[i] - 1) / 9 % 9 + 1;
        int v = (stk[i] - 1) % 9 + 1;
        ans[x][y] = v;
      }
      return 1;
    }
    IT(i, R, 0)
    if (siz[i] < siz[c])
      c = i;
    remove(c);
    IT(i, D, c)
    {
      stk[dep] = row[i];
      IT(j, R, i)
      remove(col[j]);
      if (dance(dep + 1))
        return 1;
      IT(j, L, i)
      recover(col[j]);
    }
    recover(c);
    return 0;
  }
  void load_board()
  {
    this->build(729, 324);
    for (int i = 1; i <= 9; ++i)
      for (int j = 1; j <= 9; ++j)
      {
        cin >> ans[i][j];
        for (int v = 1; v <= 9; ++v)
        {
          if (ans[i][j] && ans[i][j] != v)
            continue;
          _insert(i, j, v);
        }
      }
  }
  void solve()
  {
    this->dance(1);
    for (int i = 1; i <= 9; ++i)
    {
      for (int j = 1; j <= 9; ++j)
      {
        cout << ans[i][j] << " ";
      }
      cout << endl;
    }
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int index;
  rep(index, 0, n)
  {
    DLXSolver solver;
    solver.load_board();
    solver.solve();
  }
  return 0;
}