//https://www.hackerrank.com/challenges/kmp-fp/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

bool z_function(const string &text, const string &pattern)
{
    stringstream ss;
    ss << pattern << "$" << text;
    string s = ss.str();
    size_t n = s.length();
    vector<size_t> z(n);
    for (size_t i = 1, l = 0, r = 0; i < n; ++i)
    {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    size_t m = pattern.size();
    for (size_t c : z)
    {
        if (m == c)
            return true;
    }
    return false;
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
        if (z_function(text, pattern))
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
