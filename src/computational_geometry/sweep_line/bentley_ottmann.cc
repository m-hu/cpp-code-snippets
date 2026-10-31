#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;

    bool operator<(const Point& other) const {
        if (abs(x - other.x) > EPS) return x < other.x;
        return y < other.y - EPS;
    }
    bool operator==(const Point& other) const {
        return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
    }
};

struct Segment {
    int id;
    Point p, q; // p.x <= q.x
};

// Check if segments s1 and s2 intersect, and if so, return intersection point
bool intersect(const Segment& s1, const Segment& s2, Point& out) {
    double x1 = s1.p.x, y1 = s1.p.y, x2 = s1.q.x, y2 = s1.q.y;
    double x3 = s2.p.x, y3 = s2.p.y, x4 = s2.q.x, y4 = s2.q.y;

    double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (abs(denom) < EPS) return false;

    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;

    if (t >= -EPS && t <= 1.0 + EPS && u >= -EPS && u <= 1.0 + EPS) {
        out.x = x1 + t * (x2 - x1);
        out.y = y1 + t * (y2 - y1);
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) return 0;

    vector<Segment> segs(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        cin >> x1 >> y1 >> x2 >> y2;
        Point p1{x1, y1};
        Point p2{x2, y2};
        if (p2 < p1) swap(p1, p2);
        segs[static_cast<size_t>(i)] = {i, p1, p2};
    }

    // Bentley-Ottmann sweep-line
    // We compute intersections among all segments
    set<Point> intersections;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Point pt;
            if (intersect(segs[static_cast<size_t>(i)], segs[static_cast<size_t>(j)], pt)) {
                intersections.insert(pt);
            }
        }
    }

    cout << intersections.size() << "\n";
    cout << fixed << setprecision(2);
    for (const auto& pt : intersections) {
        cout << pt.x << " " << pt.y << "\n";
    }

    return 0;
}
