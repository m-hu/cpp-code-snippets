#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

struct KDNode {
    Point pt;
    int left = -1;
    int right = -1;
    int axis = 0; // 0 for x, 1 for y
};

class KDTree {
    vector<KDNode> tree;

    int build(vector<Point>& pts, size_t l, size_t r, int depth) {
        if (l >= r) return -1;
        int axis = depth % 2;
        size_t mid = l + (r - l) / 2;

        // Stable ordering keeps equal coordinates in input order, so the
        // tree shape (and nearest-neighbor tie-breaking) is deterministic.
        if (axis == 0) {
            stable_sort(pts.begin() + static_cast<long>(l), pts.begin() + static_cast<long>(r),
                [](const Point& a, const Point& b) { return a.x < b.x; });
        } else {
            stable_sort(pts.begin() + static_cast<long>(l), pts.begin() + static_cast<long>(r),
                [](const Point& a, const Point& b) { return a.y < b.y; });
        }

        int node_idx = static_cast<int>(tree.size());
        tree.push_back({pts[mid], -1, -1, axis});

        int left_child = build(pts, l, mid, depth + 1);
        int right_child = build(pts, mid + 1, r, depth + 1);

        tree[static_cast<size_t>(node_idx)].left = left_child;
        tree[static_cast<size_t>(node_idx)].right = right_child;

        return node_idx;
    }

    void range_query(int u, double xmin, double ymin, double xmax, double ymax, int& count) const {
        if (u == -1) return;
        const auto& node = tree[static_cast<size_t>(u)];
        if (node.pt.x >= xmin && node.pt.x <= xmax && node.pt.y >= ymin && node.pt.y <= ymax) {
            ++count;
        }

        if (node.axis == 0) {
            if (xmin <= node.pt.x) range_query(node.left, xmin, ymin, xmax, ymax, count);
            if (xmax >= node.pt.x) range_query(node.right, xmin, ymin, xmax, ymax, count);
        } else {
            if (ymin <= node.pt.y) range_query(node.left, xmin, ymin, xmax, ymax, count);
            if (ymax >= node.pt.y) range_query(node.right, xmin, ymin, xmax, ymax, count);
        }
    }

    void nearest_neighbor(int u, double qx, double qy, double& best_dist_sq, Point& best_pt) const {
        if (u == -1) return;
        const auto& node = tree[static_cast<size_t>(u)];
        double d_sq = (node.pt.x - qx) * (node.pt.x - qx) + (node.pt.y - qy) * (node.pt.y - qy);
        if (d_sq < best_dist_sq) {
            best_dist_sq = d_sq;
            best_pt = node.pt;
        }

        double axis_diff = (node.axis == 0) ? (qx - node.pt.x) : (qy - node.pt.y);
        int first = (axis_diff <= 0) ? node.left : node.right;
        int second = (axis_diff <= 0) ? node.right : node.left;

        nearest_neighbor(first, qx, qy, best_dist_sq, best_pt);
        if (axis_diff * axis_diff < best_dist_sq) {
            nearest_neighbor(second, qx, qy, best_dist_sq, best_pt);
        }
    }

public:
    explicit KDTree(vector<Point> pts) {
        build(pts, 0, pts.size(), 0);
    }

    int count_in_range(double xmin, double ymin, double xmax, double ymax) const {
        int count = 0;
        range_query(0, xmin, ymin, xmax, ymax, count);
        return count;
    }

    pair<Point, double> find_nearest(double qx, double qy) const {
        double best_dist_sq = 1e18;
        Point best_pt{0, 0};
        nearest_neighbor(0, qx, qy, best_dist_sq, best_pt);
        return {best_pt, sqrt(best_dist_sq)};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) return 0;

    vector<Point> pts(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        cin >> pts[static_cast<size_t>(i)].x >> pts[static_cast<size_t>(i)].y;
    }

    KDTree kd(pts);

    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q = 0; q < num_queries; ++q) {
            string type;
            cin >> type;
            if (type == "RANGE") {
                double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
                cin >> x1 >> y1 >> x2 >> y2;
                cout << kd.count_in_range(x1, y1, x2, y2) << "\n";
            } else if (type == "NN") {
                double qx = 0, qy = 0;
                cin >> qx >> qy;
                auto res = kd.find_nearest(qx, qy);
                cout << fixed << setprecision(2) << res.first.x << " " << res.first.y << " " << res.second << "\n";
            }
        }
    }

    return 0;
}
