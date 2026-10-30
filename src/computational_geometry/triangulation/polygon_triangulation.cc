#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <tuple>

using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    int id;
};

// Cross product of (b - a) and (c - a)
double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Check if point p is strictly inside triangle (a, b, c)
bool point_in_triangle(const Point& p, const Point& a, const Point& b, const Point& c) {
    double cp1 = cross(a, b, p);
    double cp2 = cross(b, c, p);
    double cp3 = cross(c, a, p);

    bool has_neg = (cp1 < -EPS) || (cp2 < -EPS) || (cp3 < -EPS);
    bool has_pos = (cp1 > EPS) || (cp2 > EPS) || (cp3 > EPS);

    return !(has_neg && has_pos);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) return 0;

    vector<Point> poly(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        cin >> poly[static_cast<size_t>(i)].x >> poly[static_cast<size_t>(i)].y;
        poly[static_cast<size_t>(i)].id = i;
    }

    // Ensure counter-clockwise orientation
    double signed_area = 0;
    for (size_t i = 0; i < poly.size(); ++i) {
        size_t next_i = (i + 1) % poly.size();
        signed_area += poly[i].x * poly[next_i].y - poly[next_i].x * poly[i].y;
    }
    if (signed_area < 0) {
        reverse(poly.begin(), poly.end());
    }

    struct Triangle {
        int i, j, k;
    };
    vector<Triangle> triangles;

    while (poly.size() > 3) {
        bool ear_found = false;
        size_t sz = poly.size();

        for (size_t i = 0; i < sz; ++i) {
            size_t prev_i = (i + sz - 1) % sz;
            size_t next_i = (i + 1) % sz;

            const Point& a = poly[prev_i];
            const Point& b = poly[i];
            const Point& c = poly[next_i];

            // Must be convex corner
            if (cross(a, b, c) <= EPS) continue;

            // Check if any other vertex is inside triangle (a, b, c)
            bool is_ear = true;
            for (size_t j = 0; j < sz; ++j) {
                if (j == prev_i || j == i || j == next_i) continue;
                if (point_in_triangle(poly[j], a, b, c)) {
                    is_ear = false;
                    break;
                }
            }

            if (is_ear) {
                vector<int> tri = {a.id, b.id, c.id};
                sort(tri.begin(), tri.end());
                triangles.push_back({tri[0], tri[1], tri[2]});
                poly.erase(poly.begin() + static_cast<long>(i));
                ear_found = true;
                break;
            }
        }

        if (!ear_found) break; // Should not happen for simple polygon
    }

    if (poly.size() == 3) {
        vector<int> tri = {poly[0].id, poly[1].id, poly[2].id};
        sort(tri.begin(), tri.end());
        triangles.push_back({tri[0], tri[1], tri[2]});
    }

    sort(triangles.begin(), triangles.end(), [](const Triangle& a, const Triangle& b) {
        return tie(a.i, a.j, a.k) < tie(b.i, b.j, b.k);
    });

    cout << triangles.size() << "\n";
    for (const auto& tri : triangles) {
        cout << tri.i << " " << tri.j << " " << tri.k << "\n";
    }

    return 0;
}
