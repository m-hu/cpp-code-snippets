#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;

    bool operator<(const Point& o) const {
        if (abs(x - o.x) > EPS) return x < o.x;
        return y < o.y - EPS;
    }
    bool operator==(const Point& o) const {
        return abs(x - o.x) < EPS && abs(y - o.y) < EPS;
    }
};

// Circumcircle of 3 points
bool circumcircle(const Point& a, const Point& b, const Point& c, Point& center, double& radius_sq) {
    double d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    if (abs(d) < EPS) return false;

    double ux = ((a.x * a.x + a.y * a.y) * (b.y - c.y) + (b.x * b.x + b.y * b.y) * (c.y - a.y) + (c.x * c.x + c.y * c.y) * (a.y - b.y)) / d;
    double uy = ((a.x * a.x + a.y * a.y) * (c.x - b.x) + (b.x * b.x + b.y * b.y) * (a.x - c.x) + (c.x * c.x + c.y * c.y) * (b.x - a.x)) / d;

    center = {ux, uy};
    radius_sq = (a.x - ux) * (a.x - ux) + (a.y - uy) * (a.y - uy);
    return true;
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

    // Delaunay / Voronoi vertices: every triplet of sites whose circumcircle contains no other site
    set<Point> voronoi_vertices;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                Point center;
                double r_sq = 0;
                if (!circumcircle(pts[static_cast<size_t>(i)], pts[static_cast<size_t>(j)], pts[static_cast<size_t>(k)], center, r_sq)) {
                    continue;
                }

                bool valid = true;
                for (int m = 0; m < n; ++m) {
                    if (m == i || m == j || m == k) continue;
                    double dist_sq = (pts[static_cast<size_t>(m)].x - center.x) * (pts[static_cast<size_t>(m)].x - center.x) +
                                     (pts[static_cast<size_t>(m)].y - center.y) * (pts[static_cast<size_t>(m)].y - center.y);
                    if (dist_sq < r_sq - EPS) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    voronoi_vertices.insert(center);
                }
            }
        }
    }

    cout << voronoi_vertices.size() << "\n";
    cout << fixed << setprecision(2);
    for (const auto& v : voronoi_vertices) {
        cout << v.x << " " << v.y << "\n";
    }

    return 0;
}
