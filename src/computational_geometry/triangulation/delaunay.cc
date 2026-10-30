#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

// Circumcircle of 3 points: returns center and radius squared
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

    struct Triangle {
        int i, j, k;
    };
    vector<Triangle> delaunay_triangles;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                Point center;
                double r_sq = 0;
                if (!circumcircle(pts[static_cast<size_t>(i)], pts[static_cast<size_t>(j)], pts[static_cast<size_t>(k)], center, r_sq)) {
                    continue;
                }

                bool delaunay = true;
                for (int m = 0; m < n; ++m) {
                    if (m == i || m == j || m == k) continue;
                    double dist_sq = (pts[static_cast<size_t>(m)].x - center.x) * (pts[static_cast<size_t>(m)].x - center.x) +
                                     (pts[static_cast<size_t>(m)].y - center.y) * (pts[static_cast<size_t>(m)].y - center.y);
                    if (dist_sq < r_sq - EPS) {
                        delaunay = false;
                        break;
                    }
                }

                if (delaunay) {
                    delaunay_triangles.push_back({i, j, k});
                }
            }
        }
    }

    sort(delaunay_triangles.begin(), delaunay_triangles.end(), [](const Triangle& a, const Triangle& b) {
        return tie(a.i, a.j, a.k) < tie(b.i, b.j, b.k);
    });

    cout << delaunay_triangles.size() << "\n";
    for (const auto& tri : delaunay_triangles) {
        cout << tri.i << " " << tri.j << " " << tri.k << "\n";
    }

    return 0;
}
