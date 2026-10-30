#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {

struct Point {
    long long x;
    long long y;
};

long long cross(const Point& a, const Point& b, const Point& p) {
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

bool on_segment(const Point& a, const Point& b, const Point& p) {
    if (cross(a, b, p) != 0) return false;
    return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) &&
           std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

std::string classify_point(const std::vector<Point>& poly, const Point& p) {
    int winding = 0;
    size_t n = poly.size();
    for (size_t i = 0; i < n; ++i) {
        const Point& a = poly[i];
        const Point& b = poly[(i + 1) % n];
        if (on_segment(a, b, p)) {
            return "BOUNDARY";
        }
        if (a.y <= p.y) {
            if (b.y > p.y && cross(a, b, p) > 0) {
                ++winding;
            }
        } else {
            if (b.y <= p.y && cross(a, b, p) < 0) {
                --winding;
            }
        }
    }
    return (winding != 0) ? "INSIDE" : "OUTSIDE";
}

}  // namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int q = 0;
    if (!(std::cin >> n >> q) || n < 3) return 0;

    std::vector<Point> poly(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        std::cin >> poly[static_cast<size_t>(i)].x >> poly[static_cast<size_t>(i)].y;
    }

    for (int i = 0; i < q; ++i) {
        Point pt{0, 0};
        std::cin >> pt.x >> pt.y;
        std::cout << classify_point(poly, pt) << "\n";
    }
    return 0;
}
