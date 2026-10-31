#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

double dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double closest_pair_rec(vector<Point>& pts_x, size_t l, size_t r) {
    if (r - l <= 3) {
        double min_d = 1e18;
        for (size_t i = l; i < r; ++i) {
            for (size_t j = i + 1; j < r; ++j) {
                min_d = min(min_d, dist(pts_x[i], pts_x[j]));
            }
        }
        return min_d;
    }

    size_t mid = l + (r - l) / 2;
    double mid_x = pts_x[mid].x;

    double d1 = closest_pair_rec(pts_x, l, mid);
    double d2 = closest_pair_rec(pts_x, mid, r);
    double d = min(d1, d2);

    vector<Point> strip;
    for (size_t i = l; i < r; ++i) {
        if (abs(pts_x[i].x - mid_x) < d) {
            strip.push_back(pts_x[i]);
        }
    }

    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    return d;
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

    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (abs(a.x - b.x) > 1e-9) return a.x < b.x;
        return a.y < b.y;
    });

    double ans = closest_pair_rec(pts, 0, pts.size());
    cout << fixed << setprecision(6) << ans << "\n";

    return 0;
}
