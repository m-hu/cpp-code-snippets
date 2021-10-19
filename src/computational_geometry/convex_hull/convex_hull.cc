//https://www.hackerrank.com/challenges/convex-hull-fp/problem
#include <bits/stdc++.h>
#define rep(i, l, r) for ((i) = (l); (i) < (r); (i)++)
#define all(x) (x).begin(), (x).end()
using namespace std;

double dist(const pair<int, int> &p1, const pair<int, int> &p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

double perimeter(const vector<pair<int, int>> &p)
{
    double ans = 0.0;
    for (size_t i = 0; i < p.size() - 1; ++i)
    {
        ans += dist(p[i], p[i + 1]);
    }
    ans += dist(p[0], p[p.size() - 1]);
    return ans;
}

int cross(const pair<int, int> &o,
          const pair<int, int> &a,
          const pair<int, int> &b)
{
    return ((a.first - o.first) * (b.second - o.second)) - ((a.second - o.second) * (b.first - o.first));
}

vector<pair<int, int>> hull(const vector<pair<int, int>> &points)
{
    vector<pair<int, int>> ans;
    for (pair<int, int> p : points)
    {
        while (ans.size() >= 2 && cross(ans[ans.size() - 2], ans[ans.size() - 1], p) <= 0)
        {
            ans.pop_back();
        }
        ans.push_back(p);
    }
    ans.pop_back();
    return ans;
}

vector<pair<int, int>> convex_hull(const vector<pair<int, int>> &points)
{
    set<pair<int, int>> distinct_points(points.begin(), points.end());
    if (distinct_points.size() > 2)
    {
        vector<pair<int, int>> sorted_points(distinct_points.begin(), distinct_points.end());
        vector<pair<int, int>> lower = hull(sorted_points);
        reverse(sorted_points.begin(), sorted_points.end());
        vector<pair<int, int>> upper = hull(sorted_points);
        lower.insert(lower.end(), upper.begin(), upper.end());
        return lower;
    }
    return {};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> points[i].first >> points[i].second;
    }
    cout << fixed << setprecision(1) << perimeter(convex_hull(points)) << endl;
    return 0;
}
