// crc: polynomial modulo-2 division remainder (Tanenbaum networks).
// Pure C++14. Input: generator binary string; message binary string.
// Output: remainder of length len(G)-1.
#include <iostream>
#include <string>
#include <vector>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string G, M;
    if (!(std::cin >> G)) return 0;
    std::cin >> M;
    int r = (int)G.size() - 1;
    std::vector<int> d;
    for (char c : M) d.push_back(c == '1' ? 1 : 0);
    for (int i = 0; i < r; ++i) d.push_back(0);
    for (size_t i = 0; i < M.size(); ++i) {
        if (d[i] == 1) {
            for (size_t j = 0; j < G.size(); ++j)
                d[i + j] ^= (G[j] == '1' ? 1 : 0);
        }
    }
    for (size_t i = M.size(); i < d.size(); ++i) std::cout << d[i];
    std::cout << "\n";
    return 0;
}
