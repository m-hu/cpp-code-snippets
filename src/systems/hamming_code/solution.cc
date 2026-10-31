// hamming-code: SEC-DED syndrome decoding with overall parity.
// Pure C++14. Line1: q ops. E <data> -> codeword; C <code> ->
// "<data> OK|FIXED|DED".
#include <iostream>
#include <string>
#include <vector>
static int npar(int k) {
    int p = 0;
    while ((1 << p) < k + p + 1) ++p;
    return p;
}
static bool ispow2(int x) { return x && !(x & (x - 1)); }
static std::string encode(const std::string &data) {
    int k = data.size(), p = npar(k), hlen = k + p;
    std::vector<int> h(hlen + 1, 0); // 1-based
    int di = 0;
    for (int i = 1; i <= hlen; ++i)
        if (!ispow2(i)) h[i] = data[di++] == '1' ? 1 : 0;
    for (int b = 0; b < p; ++b) {
        int s = 0;
        for (int i = 1; i <= hlen; ++i)
            if (i & (1 << b)) s ^= h[i];
        h[1 << b] = s;
    }
    int p0 = 0;
    for (int i = 1; i <= hlen; ++i) p0 ^= h[i];
    std::string out;
    out += p0 ? '1' : '0';
    for (int i = 1; i <= hlen; ++i) out += h[i] ? '1' : '0';
    return out;
}
static std::pair<std::string, std::string> decode(const std::string &code) {
    int hlen = (int)code.size() - 1;
    std::vector<int> h(hlen + 1, 0);
    int p0 = code[0] == '1' ? 1 : 0;
    for (int i = 1; i <= hlen; ++i) h[i] = code[i] == '1' ? 1 : 0;
    int p = 0;
    while ((1 << p) <= hlen) ++p;
    int syn = 0;
    for (int b = 0; b < p; ++b) {
        int s = 0;
        for (int i = 1; i <= hlen; ++i)
            if (i & (1 << b)) s ^= h[i];
        if (s) syn |= (1 << b);
    }
    int tot = p0;
    for (int i = 1; i <= hlen; ++i) tot ^= h[i];
    std::string status;
    if (syn == 0 && tot == 0) status = "OK";
    else if (syn == 0) { status = "FIXED"; p0 ^= 1; }
    else if (tot != 0) { status = "FIXED"; h[syn] ^= 1; }
    else status = "DED";
    std::string data;
    for (int i = 1; i <= hlen; ++i)
        if (!ispow2(i)) data += h[i] ? '1' : '0';
    return {data, status};
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    for (int i = 0; i < q; ++i) {
        char op;
        std::string w;
        std::cin >> op >> w;
        if (op == 'E') {
            std::cout << encode(w) << "\n";
        } else {
            auto pr = decode(w);
            std::cout << pr.first << " " << pr.second << "\n";
        }
    }
    return 0;
}
