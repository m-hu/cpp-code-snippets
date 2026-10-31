#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace {

struct Point {
    long long x;
    long long y;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Disc {
    double cx;
    double cy;
    double r2;
};

double dist_sq(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return dx * dx + dy * dy;
}

bool in_disc(const Disc& d, const Point& p) {
    return dist_sq(d.cx, d.cy, static_cast<double>(p.x), static_cast<double>(p.y)) <= d.r2 + 1e-9;
}

Disc disc_from_2(const Point& a, const Point& b) {
    double cx = 0.5 * static_cast<double>(a.x + b.x);
    double cy = 0.5 * static_cast<double>(a.y + b.y);
    double dx = static_cast<double>(b.x - a.x);
    double dy = static_cast<double>(b.y - a.y);
    return Disc{cx, cy, 0.25 * (dx * dx + dy * dy)};
}

Disc disc_from_3(const Point& a, const Point& b, const Point& c) {
    long long bx_i = b.x - a.x;
    long long by_i = b.y - a.y;
    long long cx_i = c.x - a.x;
    long long cy_i = c.y - a.y;
    long long det = bx_i * cy_i - by_i * cx_i;
    if (det == 0) {
        Disc d1 = disc_from_2(a, b);
        Disc d2 = disc_from_2(a, c);
        Disc d3 = disc_from_2(b, c);
        Disc best = d1;
        if (d2.r2 > best.r2) best = d2;
        if (d3.r2 > best.r2) best = d3;
        return best;
    }
    double bx = static_cast<double>(bx_i);
    double by = static_cast<double>(by_i);
    double cx = static_cast<double>(cx_i);
    double cy = static_cast<double>(cy_i);
    double b2 = bx * bx + by * by;
    double c2 = cx * cx + cy * cy;
    double d = 2.0 * static_cast<double>(det);
    double ux = (cy * b2 - by * c2) / d;
    double uy = (bx * c2 - cx * b2) / d;
    return Disc{static_cast<double>(a.x) + ux, static_cast<double>(a.y) + uy, ux * ux + uy * uy};
}

Disc mini_disc_with_2_points(const std::vector<Point>& pts, size_t limit, const Point& q1, const Point& q2) {
    Disc d = disc_from_2(q1, q2);
    for (size_t k = 0; k < limit; ++k) {
        if (!in_disc(d, pts[k])) {
            d = disc_from_3(q1, q2, pts[k]);
        }
    }
    return d;
}

Disc mini_disc_with_point(const std::vector<Point>& pts, size_t limit, const Point& q) {
    Disc d = disc_from_2(pts[0], q);
    for (size_t j = 1; j < limit; ++j) {
        if (!in_disc(d, pts[j])) {
            d = mini_disc_with_2_points(pts, j, pts[j], q);
        }
    }
    return d;
}

Disc welzl_mini_disc(std::vector<Point> pts) {
    std::sort(pts.begin(), pts.end());
    pts.erase(std::unique(pts.begin(), pts.end()), pts.end());
    if (pts.empty()) return Disc{0.0, 0.0, 0.0};
    if (pts.size() == 1) {
        return Disc{static_cast<double>(pts[0].x), static_cast<double>(pts[0].y), 0.0};
    }
    Disc d = disc_from_2(pts[0], pts[1]);
    for (size_t i = 2; i < pts.size(); ++i) {
        if (!in_disc(d, pts[i])) {
            d = mini_disc_with_point(pts, i, pts[i]);
        }
    }
    return d;
}

}  // namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<Point> pts(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        std::cin >> pts[static_cast<size_t>(i)].x >> pts[static_cast<size_t>(i)].y;
    }

    Disc ans = welzl_mini_disc(pts);
    long long cx_out = std::llround(ans.cx * 1000.0);
    long long cy_out = std::llround(ans.cy * 1000.0);
    long long r2_out = std::llround(ans.r2 * 1000.0);
    std::cout << cx_out << " " << cy_out << " " << r2_out << "\n";
    return 0;
}
