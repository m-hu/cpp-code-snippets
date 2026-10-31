#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

const int MAX_LEVEL = 16;

struct SkipNode {
    int val;
    vector<SkipNode*> forward;
    SkipNode(int v, int level) : val(v), forward(static_cast<size_t>(level + 1), nullptr) {}
};

class SkipList {
    SkipNode* head;
    int current_level = 0;
    mt19937 rng{42}; // Deterministic seed

    int random_level() {
        int lvl = 0;
        while ((rng() & 1) && lvl < MAX_LEVEL) {
            ++lvl;
        }
        return lvl;
    }

public:
    SkipList() {
        head = new SkipNode(-1, MAX_LEVEL);
    }

    ~SkipList() {
        SkipNode* cur = head;
        while (cur) {
            SkipNode* next = cur->forward[0];
            delete cur;
            cur = next;
        }
    }

    void insert(int val) {
        vector<SkipNode*> update(static_cast<size_t>(MAX_LEVEL + 1), nullptr);
        SkipNode* cur = head;

        for (int i = current_level; i >= 0; --i) {
            while (cur->forward[static_cast<size_t>(i)] && cur->forward[static_cast<size_t>(i)]->val < val) {
                cur = cur->forward[static_cast<size_t>(i)];
            }
            update[static_cast<size_t>(i)] = cur;
        }

        cur = cur->forward[0];
        if (cur && cur->val == val) return; // Already exists

        int rlevel = random_level();
        if (rlevel > current_level) {
            for (int i = current_level + 1; i <= rlevel; ++i) {
                update[static_cast<size_t>(i)] = head;
            }
            current_level = rlevel;
        }

        SkipNode* new_node = new SkipNode(val, rlevel);
        for (int i = 0; i <= rlevel; ++i) {
            new_node->forward[static_cast<size_t>(i)] = update[static_cast<size_t>(i)]->forward[static_cast<size_t>(i)];
            update[static_cast<size_t>(i)]->forward[static_cast<size_t>(i)] = new_node;
        }
    }

    bool search(int val) const {
        SkipNode* cur = head;
        for (int i = current_level; i >= 0; --i) {
            while (cur->forward[static_cast<size_t>(i)] && cur->forward[static_cast<size_t>(i)]->val < val) {
                cur = cur->forward[static_cast<size_t>(i)];
            }
        }
        cur = cur->forward[0];
        return cur && cur->val == val;
    }

    void remove(int val) {
        vector<SkipNode*> update(static_cast<size_t>(MAX_LEVEL + 1), nullptr);
        SkipNode* cur = head;

        for (int i = current_level; i >= 0; --i) {
            while (cur->forward[static_cast<size_t>(i)] && cur->forward[static_cast<size_t>(i)]->val < val) {
                cur = cur->forward[static_cast<size_t>(i)];
            }
            update[static_cast<size_t>(i)] = cur;
        }

        cur = cur->forward[0];
        if (cur && cur->val == val) {
            for (int i = 0; i <= current_level; ++i) {
                if (update[static_cast<size_t>(i)]->forward[static_cast<size_t>(i)] != cur) break;
                update[static_cast<size_t>(i)]->forward[static_cast<size_t>(i)] = cur->forward[static_cast<size_t>(i)];
            }
            delete cur;
            while (current_level > 0 && head->forward[static_cast<size_t>(current_level)] == nullptr) {
                --current_level;
            }
        }
    }

    vector<int> get_all() const {
        vector<int> res;
        SkipNode* cur = head->forward[0];
        while (cur) {
            res.push_back(cur->val);
            cur = cur->forward[0];
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q = 0;
    if (!(cin >> q)) return 0;

    SkipList sl;
    for (int i = 0; i < q; ++i) {
        string op;
        cin >> op;
        if (op == "INSERT") {
            int val = 0;
            cin >> val;
            sl.insert(val);
        } else if (op == "SEARCH") {
            int val = 0;
            cin >> val;
            cout << (sl.search(val) ? "FOUND\n" : "NOT_FOUND\n");
        } else if (op == "DELETE") {
            int val = 0;
            cin >> val;
            sl.remove(val);
        } else if (op == "PRINT") {
            auto arr = sl.get_all();
            for (size_t j = 0; j < arr.size(); ++j) {
                if (j > 0) cout << " ";
                cout << arr[j];
            }
            cout << "\n";
        }
    }

    return 0;
}
