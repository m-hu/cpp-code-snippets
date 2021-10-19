//https://www.hackerrank.com/challenges/string-function-calculation
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

struct triple {
  int originalIndex;
  int firstHalf;
  int secondHalf;
};

int cmp(const triple &a, const triple &b) {
  if (a.firstHalf == b.firstHalf)
    return a.secondHalf < b.secondHalf;
  else
    return a.firstHalf < b.firstHalf;
}

vector<int> cal_suffix_array(const string &t) {
  int n = static_cast<int>(t.size());
  vector<int> suffix_array;
  vector<vector<int>> suffix_rank(26, vector<int>(int(1E6)));
  for (int i = 0; i < n; ++i) {
    suffix_rank[0][i] = t[i] - 'a';
  }

  vector<triple> L(n);

  for (int cnt = 1, stp = 1; cnt < n; cnt *= 2, ++stp) {

    for (int i = 0; i < n; ++i) {
      L[i].firstHalf = suffix_rank[stp - 1][i];
      L[i].secondHalf = i + cnt < n ? suffix_rank[stp - 1][i + cnt] : -1;
      L[i].originalIndex = i;
    }

    // On the basis of triples obtained sort the triple array
    sort(L.begin(), L.end(), cmp);

    // Initialize rank for rank 0 suffix after sorting to its original index
    // in suffixRank array

    suffix_rank[stp][L[0].originalIndex] = 0;

    for (int i = 1, currRank = 0; i < n; ++i) {

      // compare ith ranked suffix ( after sorting ) to (i - 1)th ranked suffix
      // if they are equal till now assign same rank to ith as that of (i - 1)th
      // else rank for ith will be currRank ( i.e. rank of (i - 1)th ) plus 1,
      // i.e ( currRank + 1 )

      if (L[i - 1].firstHalf != L[i].firstHalf
          || L[i - 1].secondHalf != L[i].secondHalf)
        ++currRank;

      suffix_rank[stp][L[i].originalIndex] = currRank;
    }
  }

  for (int i = 0; i < n; ++i) {
    suffix_array.push_back(L[i].originalIndex);
  }

  return suffix_array;
}

vector<int> kasai(string s, vector<int> sa) {
  int n = static_cast<int>(s.size()), k = 0;
  vector<int> lcp(n, 0);
  vector<int> rank(n, 0);

  for (int i = 0; i < n; i++)
    rank[sa[i]] = i;

  for (int i = 0; i < n; i++, k ? k-- : 0) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }
    int j = sa[rank[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k])
      k++;
    lcp[rank[i]] = k;
  }
  return lcp;
}

int max_value(string t) {
  vector<int> suffix_array = cal_suffix_array(t);
  vector<int> lcp = kasai(t, suffix_array);
  int n = static_cast<int>(t.size());
  int ans = n;
  // in the worst case, every character is distinct
  for (int i = 1; i < n; i++) {
    int cnt = 2;
    for (int j = i - 1; j >= 0; j--) {
      if (lcp[j] >= lcp[i])
        cnt++;
      else
        break;
    }
    for (int j = i + 1; j < n; j++) {
      if (lcp[j] >= lcp[i])
        cnt++;
      else
        break;
    }
    // check the substring represented by the longest common prefix lcp[i]
    // then find the max
    ans = max(ans, cnt * lcp[i]);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int t = max_value(s);
  cout << t << endl;
  return 0;
}
