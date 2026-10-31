//https://www.hackerrank.com/challenges/kmp-fp/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

void build_dfa(vector<vector<size_t>> &dfa, const string &pattern, size_t R, size_t M)
{
    dfa[pattern[0]][0] = 1;
    for (size_t X = 0, j = 1; j < M; ++j)
    {
        for (size_t c = 0; c < R; ++c)
        {
            dfa[c][j] = dfa[c][X];
        }
        dfa[pattern[j]][j] = j + 1;
        X = dfa[pattern[j]][X];
    }
}

bool search(const string &text, const vector<vector<size_t>> &dfa)
{
    size_t i, j;
    size_t N = text.size();
    size_t M = dfa[0].size();
    for (i = 0, j = 0; i < N && j < M; ++i)
    {
        j = dfa[text[i]][j];
    }
    if (j == M)
        return true;
    else
        return false;
}

bool kmp(const string &text, const string &pattern)
{
    size_t R = 256;
    size_t M = pattern.size();
    vector<vector<size_t>> dfa(R, vector<size_t>(M, 0));
    build_dfa(dfa, pattern, R, M);
    return search(text, dfa);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string text;
        string pattern;
        cin >> text >> pattern;
        if (kmp(text, pattern))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}
