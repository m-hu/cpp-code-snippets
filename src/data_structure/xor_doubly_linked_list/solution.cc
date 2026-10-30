// xor-doubly-linked-list: memory-efficient deque (Karumanchi Ch 3).
// Each node stores prev^next (index+1 encoding, 0=null) in one field.
// Ops: 1 x push_front, 2 x push_back, 3 pop_front, 4 pop_back, 5 print.
#include <cstdint>
#include <iostream>
#include <vector>
struct XorList {
    std::vector<int64_t> val;
    std::vector<int> link;
    int head, tail;
    XorList() : head(-1), tail(-1) {}
    int alloc(int64_t x) {
        val.push_back(x);
        link.push_back(0);
        return (int)val.size() - 1;
    }
    void push_front(int64_t x) {
        int n = alloc(x);
        link[n] = (0 ^ (head + 1));
        if (head == -1) { head = tail = n; return; }
        link[head] = link[head] ^ (n + 1);
        head = n;
    }
    void push_back(int64_t x) {
        int n = alloc(x);
        link[n] = ((tail + 1) ^ 0);
        if (tail == -1) { head = tail = n; return; }
        link[tail] = link[tail] ^ (n + 1);
        tail = n;
    }
    bool pop_front(int64_t &o) {
        if (head == -1) return false;
        o = val[head];
        int nxt = link[head] ^ 0;
        if (nxt == 0) { head = tail = -1; return true; }
        int ni = nxt - 1;
        link[ni] = link[ni] ^ (head + 1);
        head = ni;
        return true;
    }
    bool pop_back(int64_t &o) {
        if (tail == -1) return false;
        o = val[tail];
        int prv = link[tail] ^ 0;
        if (prv == 0) { head = tail = -1; return true; }
        int pi = prv - 1;
        link[pi] = link[pi] ^ (tail + 1);
        tail = pi;
        return true;
    }
    void print() {
        bool first = true;
        int prev = -1, cur = head;
        while (cur != -1) {
            if (!first) std::cout << " ";
            first = false;
            std::cout << val[cur];
            int nxt = link[cur] ^ (prev + 1);
            prev = cur;
            cur = (nxt == 0) ? -1 : nxt - 1;
        }
        std::cout << "\n";
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int q = 0;
    if (!(std::cin >> q)) return 0;
    XorList l;
    for (int i = 0; i < q; ++i) {
        int op = 0;
        std::cin >> op;
        if (op == 1) { int64_t x; std::cin >> x; l.push_front(x); }
        else if (op == 2) { int64_t x; std::cin >> x; l.push_back(x); }
        else if (op == 3) { int64_t o; if (l.pop_front(o)) std::cout << o << "\n"; else std::cout << "EMPTY\n"; }
        else if (op == 4) { int64_t o; if (l.pop_back(o)) std::cout << o << "\n"; else std::cout << "EMPTY\n"; }
        else if (op == 5) { l.print(); }
    }
    return 0;
}
