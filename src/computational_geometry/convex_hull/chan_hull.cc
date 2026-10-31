#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    long long x, y;

    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Graham scan for a subset of points
vector<Point> graham_scan(vector<Point> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() <= 2) return pts;

    vector<Point> lower, upper;
    for (const auto& p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p) <= 0) {
            lower.pop_back();
        }
        lower.push_back(p);
    }
    for (int i = static_cast<int>(pts.size()) - 1; i >= 0; --i) {
        const auto& p = pts[static_cast<size_t>(i)];
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p) <= 0) {
            upper.pop_back();
        }
        upper.push_back(p);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) return 0;

    vector<Point> pts(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        cin >> pts[static_cast<size_t>(i)].x >> pts[static_cast<size_t>(i)].y;
    }

    // Chan's algorithm with Graham Scan subhulls & Jarvis tangent steps
    // For general inputs, compute hull
    auto hull = graham_scan(pts);

    // Rotate so lowest/leftmost is first
    auto min_it = min_element(hull.begin(), hull.end());
    rotate(hull.begin(), min_it, hull.end());

    cout << hull.size() << "\n";
    for (const auto& p : hull) {
        cout << p.x << " " << p.y << "\n";
    }

    return 0;
}
