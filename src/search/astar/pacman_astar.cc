/*
 * https://www.hackerrank.com/challenges/pacman-astar/problem
 *
 */
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); ++(i))
#define all(x) (x).begin(), (x).end()

using namespace std;

/**
 * @class node
 * @brief helper class for A star
 *
 */
class node {
 public:
  pair<int, int> position;
  int cost;
  node()
      :
      position( { -1, -1 }),
      cost(-1) {
  }
  node(pair<int, int> p, int c)
      :
      position(p),
      cost(c) {

  }
};

/**
 * @struct CompareNode
 * @brief Comparator of the node type, to make min heap
 *
 */
struct CompareNode {
  bool operator()(const node &lhs, const node &rhs) {
    return make_tuple(lhs.cost, lhs.position.first, lhs.position.second)
        < make_tuple(rhs.cost, rhs.position.first, rhs.position.second);
  }
};

/**
 * @fn vector<pair<int,int>> neighbours(const vector<string>&, const pair<int,int>&)
 * @brief get neighbours of the current cell TODO implement an iterator version for memory efficiency
 *
 * @param matrix
 * @param p
 * @return
 */
vector<pair<int, int> > neighbours(const vector<string> &matrix,
                                   const pair<int, int> &p) {
  int n = static_cast<int>(matrix.size());
  int m = static_cast<int>(matrix[0].size());
  vector<pair<int, int>> neighbours;
  pair<int, int> up = { p.first - 1, p.second };
  pair<int, int> left = { p.first, p.second - 1 };
  pair<int, int> right = { p.first, p.second + 1 };
  pair<int, int> down = { p.first + 1, p.second };
  for (const pair<int, int> &c : { up, left, right, down }) {
    if (c.first >= 0 && c.first < n && c.second >= 0 && c.second < m
        && matrix[c.first][c.second] != '%') {
      neighbours.push_back(c);
    }
  }
  return neighbours;
}

int manhattan(pair<int, int> s, pair<int, int> d) {
  return abs(d.first - s.first) + abs(d.second - s.second);
}

/**
 * @fn vector<pair<int,int>> astar(const vector<string>&, const pair<int,int>&, const pair<int,int>&)
 * @brief an a star implementation, to be tested with larger test cases
 *
 * @param matrix
 * @param pacman
 * @param food
 * @return
 */
vector<pair<int, int> > astar(const vector<string> &matrix,
                              const pair<int, int> &pacman,
                              const pair<int, int> &food) {
  vector<pair<int, int>> tracks;
  if (!matrix.empty()) {
    int n = static_cast<int>(matrix.size());
    int m = static_cast<int>(matrix[0].size());
    vector<vector<int> > dist(n, vector<int>(m, -1));
    vector<vector<node> > paths(n, vector<node>(m));
    /*
     * It is used to memorize the node already put into the queue.
     * Perhaps it could be simplified by using the reference/pointer
     * of the node but it does not work with the current implementation of set
     * provided by stl, because the set will not be updated upon any node attribute change
     */
    vector<vector<node> > node_index(n, vector<node>(m));
    set<node, CompareNode> q;
    q.insert(node(pacman, manhattan(pacman, food)));
    dist[pacman.first][pacman.second] = 0;
    while (!q.empty()) {
      node current = *(q.begin());
      q.erase(q.begin());  // cannot be simplified, there would be revisit if necessary
      for (pair<int, int> neighbour : neighbours(matrix, current.position)) {
        int new_dist = dist[current.position.first][current.position.second]
            + 1;
        int new_cost = dist[current.position.first][current.position.second]
            + manhattan(neighbour, food);
        if (dist[neighbour.first][neighbour.second] == -1
            || dist[neighbour.first][neighbour.second] > new_dist) {
          if (dist[neighbour.first][neighbour.second] != -1) {
            node old_node = node_index[neighbour.first][neighbour.second];
            q.erase(q.find(old_node));
          }
          dist[neighbour.first][neighbour.second] = new_dist;
          paths[neighbour.first][neighbour.second] = current;
          node new_node = node(neighbour, new_cost);
          q.insert(new_node);
          node_index[neighbour.first][neighbour.second] = new_node;
        }
      }
    }
    pair<int, int> step = food;
    tracks.push_back(step);
    while (step != pacman) {
      step = paths[step.first][step.second].position;
      tracks.push_back(step);
    }
  }
  reverse(all(tracks));
  return tracks;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  pair<int, int> pacman;
  pair<int, int> food;
  int n, m;
  cin >> pacman.first >> pacman.second;
  cin >> food.first >> food.second;
  cin >> n >> m;
  vector<string> matrix(n, string(m, ' '));
  int i;
  rep(i, 0, n)
  {
    int j;
    rep(j, 0, m)
    {
      cin >> matrix[i][j];
    }
  }
  vector<pair<int, int> > tracks = astar(matrix, pacman, food);
  if (!tracks.empty()) {
    cout << tracks.size() - 1 << endl;
    for (const pair<int, int> &track : tracks) {
      cout << track.first << " " << track.second << endl;
    }
  }
  return 0;
}
