//https://www.hackerrank.com/challenges/kmp-fp/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;
void build_suffix(vector<long> &right, const string &pattern)
{
    for (size_t j = 0; j < pattern.size(); ++j)
    {
        right[pattern[j]] = static_cast<long>(j);
    }
}

bool boyer_moore(const string &text, const string &pattern)
{
    vector<long> right(256, -1);
    build_suffix(right, pattern);
    size_t N = text.size();
    size_t M = pattern.size();
    long skip = 0;
    for (size_t i = 0; i <= N - M; i += skip)
    {
        skip = 0;
        for (long j = M - 1; j >= 0; --j)
        {
            if (pattern[j] != text[i + j])
            {
                skip = j - right[text[i + j]];
                if (skip < 1)
                    skip = 1;
                break;
            }
        }
        if (skip == 0)
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
        if (boyer_moore(text, pattern))
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
