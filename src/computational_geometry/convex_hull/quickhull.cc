#include <algorithm>
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

long long cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

void build_hull(const Point& p, const Point& q, const std::vector<Point>& pts, std::vector<Point>& out) {
    if (pts.empty()) return;
    size_t best_idx = 0;
    long long best_dist = cross(q, p, pts[0]);
    for (size_t i = 1; i < pts.size(); ++i) {
        long long d = cross(q, p, pts[i]);
        if (d > best_dist || (d == best_dist && pts[i] < pts[best_idx])) {
            best_dist = d;
            best_idx = i;
        }
    }
    Point c = pts[best_idx];
    std::vector<Point> left_pc;
    std::vector<Point> left_cq;
    for (const auto& pt : pts) {
        if (cross(c, p, pt) > 0) {
            left_pc.push_back(pt);
        } else if (cross(q, c, pt) > 0) {
            left_cq.push_back(pt);
        }
    }
    build_hull(p, c, left_pc, out);
    out.push_back(c);
    build_hull(c, q, left_cq, out);
}

std::vector<Point> quickhull(std::vector<Point> pts) {
    std::sort(pts.begin(), pts.end());
    pts.erase(std::unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() <= 2) return pts;

    Point a = pts.front();
    Point b = pts.back();
    std::vector<Point> lower_pts;
    std::vector<Point> upper_pts;
    for (size_t i = 1; i + 1 < pts.size(); ++i) {
        long long cp = cross(a, b, pts[i]);
        if (cp < 0) {
            lower_pts.push_back(pts[i]);
        } else if (cp > 0) {
            upper_pts.push_back(pts[i]);
        }
    }
    if (lower_pts.empty() && upper_pts.empty()) {
        return {a, b};
    }

    std::vector<Point> raw;
    raw.push_back(a);
    build_hull(a, b, lower_pts, raw);
    raw.push_back(b);
    build_hull(b, a, upper_pts, raw);

    // Strip any collinear boundary points produced by distance ties.
    std::vector<Point> hull;
    size_t m = raw.size();
    for (size_t i = 0; i < m; ++i) {
        const Point& prev = raw[(i + m - 1) % m];
        const Point& curr = raw[i];
        const Point& next = raw[(i + 1) % m];
        if (cross(prev, curr, next) > 0) {
            hull.push_back(curr);
        }
    }
    auto min_it = std::min_element(hull.begin(), hull.end());
    std::rotate(hull.begin(), min_it, hull.end());
    return hull;
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

    std::vector<Point> hull = quickhull(pts);
    for (const auto& p : hull) {
        std::cout << p.x << " " << p.y << "\n";
    }
    return 0;
}
