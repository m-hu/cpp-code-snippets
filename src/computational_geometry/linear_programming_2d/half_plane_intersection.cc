#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <vector>

namespace {

long long gcd_ll(long long a, long long b) {
    a = std::llabs(a);
    b = std::llabs(b);
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

struct HalfPlane {
    long long dx;
    long long dy;
    long long c;  // -dy * x + dx * y >= c

    int half() const {
        return (dy > 0 || (dy == 0 && dx > 0)) ? 0 : 1;
    }

    bool operator<(const HalfPlane& other) const {
        int h1 = half();
        int h2 = other.half();
        if (h1 != h2) return h1 < h2;
        long long cr = dx * other.dy - dy * other.dx;
        if (cr != 0) return cr > 0;
        return c > other.c;
    }
};

struct PointD {
    double x;
    double y;
};

bool is_outside(const HalfPlane& h, const PointD& p) {
    double lhs = -static_cast<double>(h.dy) * p.x + static_cast<double>(h.dx) * p.y;
    return lhs < static_cast<double>(h.c) - 1e-9;
}

PointD intersect(const HalfPlane& h1, const HalfPlane& h2) {
    double det = static_cast<double>(h1.dx * h2.dy - h1.dy * h2.dx);
    double c1 = static_cast<double>(h1.c);
    double c2 = static_cast<double>(h2.c);
    double x = (c1 * static_cast<double>(h2.dx) - static_cast<double>(h1.dx) * c2) / det;
    double y = (c1 * static_cast<double>(h2.dy) - static_cast<double>(h1.dy) * c2) / det;
    return PointD{x, y};
}

}  // namespace

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    if (!(std::cin >> n) || n <= 0) return 0;

    std::vector<HalfPlane> raw;
    raw.reserve(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        long long x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        std::cin >> x1 >> y1 >> x2 >> y2;
        long long dx = x2 - x1;
        long long dy = y2 - y1;
        long long g = gcd_ll(dx, dy);
        if (g == 0) continue;
        dx /= g;
        dy /= g;
        long long c = dx * y1 - dy * x1;
        raw.push_back(HalfPlane{dx, dy, c});
    }

    std::sort(raw.begin(), raw.end());
    std::vector<HalfPlane> hps;
    for (const auto& h : raw) {
        if (hps.empty() || hps.back().dx != h.dx || hps.back().dy != h.dy) {
            hps.push_back(h);
        }
    }

    std::deque<HalfPlane> dq;
    for (const auto& h : hps) {
        while (dq.size() >= 2 && is_outside(h, intersect(dq[dq.size() - 2], dq.back()))) {
            dq.pop_back();
        }
        while (dq.size() >= 2 && is_outside(h, intersect(dq[0], dq[1]))) {
            dq.pop_front();
        }
        if (!dq.empty() && (dq.back().dx * h.dy - dq.back().dy * h.dx) == 0) {
            std::cout << "0 0\n";
            return 0;
        }
        dq.push_back(h);
    }

    while (dq.size() >= 3 && is_outside(dq.front(), intersect(dq[dq.size() - 2], dq.back()))) {
        dq.pop_back();
    }
    while (dq.size() >= 3 && is_outside(dq.back(), intersect(dq[0], dq[1]))) {
        dq.pop_front();
    }

    if (dq.size() < 3) {
        std::cout << "0 0\n";
        return 0;
    }

    std::vector<PointD> verts;
    size_t m = dq.size();
    for (size_t i = 0; i < m; ++i) {
        const HalfPlane& h1 = dq[i];
        const HalfPlane& h2 = dq[(i + 1) % m];
        if ((h1.dx * h2.dy - h1.dy * h2.dx) <= 0) {
            std::cout << "0 0\n";
            return 0;
        }
        PointD pt = intersect(h1, h2);
        if (verts.empty() || std::hypot(pt.x - verts.back().x, pt.y - verts.back().y) > 1e-7) {
            verts.push_back(pt);
        }
    }
    if (verts.size() >= 2 && std::hypot(verts.front().x - verts.back().x, verts.front().y - verts.back().y) <= 1e-7) {
        verts.pop_back();
    }

    if (verts.size() < 3) {
        std::cout << "0 0\n";
        return 0;
    }

    double area2 = 0.0;
    size_t v = verts.size();
    for (size_t i = 0; i < v; ++i) {
        const PointD& a = verts[i];
        const PointD& b = verts[(i + 1) % v];
        area2 += a.x * b.y - a.y * b.x;
    }
    double area = 0.5 * std::fabs(area2);
    if (area <= 1e-9) {
        std::cout << "0 0\n";
        return 0;
    }

    long long area_out = std::llround(area * 1000.0);
    std::cout << v << " " << area_out << "\n";
    return 0;
}
