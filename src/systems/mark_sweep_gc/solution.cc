// mark-sweep-gc: conservative mark-and-sweep collector (Tanenbaum MOS).
// Pure C++14. Input: n r; r roots; n lines k refs.... Output: sorted
// freed ids, or NONE.
#include <algorithm>
#include <iostream>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n = 0, r = 0;
    if (!(std::cin >> n >> r)) return 0;
    std::vector<int> roots(r);
    for (int i = 0; i < r; ++i) std::cin >> roots[i];
    std::vector<std::vector<int>> refs(n);
    for (int i = 0; i < n; ++i) {
        int k = 0;
        std::cin >> k;
        refs[i].resize(k);
        for (int j = 0; j < k; ++j) std::cin >> refs[i][j];
    }
    std::vector<char> marked(n, 0);
    std::vector<int> stack;
    for (int rt : roots) {
        if (rt < 0 || rt >= n || marked[rt]) continue;
        marked[rt] = 1;
        stack.push_back(rt);
        while (!stack.empty()) {
            int u = stack.back(); stack.pop_back();
            for (int v : refs[u]) {
                if (v < 0 || v >= n || marked[v]) continue;
                marked[v] = 1;
                stack.push_back(v);
            }
        }
    }
    std::vector<int> freed;
    for (int i = 0; i < n; ++i) if (!marked[i]) freed.push_back(i);
    if (freed.empty()) {
        std::cout << "NONE\n";
    } else {
        for (size_t i = 0; i < freed.size(); ++i) {
            if (i) std::cout << " ";
            std::cout << freed[i];
        }
        std::cout << "\n";
    }
    return 0;
}
