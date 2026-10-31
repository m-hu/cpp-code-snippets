#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct State {
    int len = 0;
    int link = -1;
    map<char, int> next;
};

class SuffixAutomaton {
    vector<State> st;
    int last = 0;

public:
    SuffixAutomaton() {
        st.emplace_back(); // State 0 (root)
        st[0].len = 0;
        st[0].link = -1;
        last = 0;
    }

    void extend(char c) {
        int cur = static_cast<int>(st.size());
        st.emplace_back();
        st[static_cast<size_t>(cur)].len = st[static_cast<size_t>(last)].len + 1;

        int p = last;
        while (p != -1 && st[static_cast<size_t>(p)].next.find(c) == st[static_cast<size_t>(p)].next.end()) {
            st[static_cast<size_t>(p)].next[c] = cur;
            p = st[static_cast<size_t>(p)].link;
        }

        if (p == -1) {
            st[static_cast<size_t>(cur)].link = 0;
        } else {
            int q = st[static_cast<size_t>(p)].next[c];
            if (st[static_cast<size_t>(p)].len + 1 == st[static_cast<size_t>(q)].len) {
                st[static_cast<size_t>(cur)].link = q;
            } else {
                int clone = static_cast<int>(st.size());
                st.push_back(st[static_cast<size_t>(q)]);
                st[static_cast<size_t>(clone)].len = st[static_cast<size_t>(p)].len + 1;

                while (p != -1 && st[static_cast<size_t>(p)].next[c] == q) {
                    st[static_cast<size_t>(p)].next[c] = clone;
                    p = st[static_cast<size_t>(p)].link;
                }

                st[static_cast<size_t>(q)].link = clone;
                st[static_cast<size_t>(cur)].link = clone;
            }
        }
        last = cur;
    }

    size_t state_count() const {
        return st.size();
    }

    size_t transition_count() const {
        size_t total = 0;
        for (const auto& s : st) {
            total += s.next.size();
        }
        return total;
    }

    long long distinct_substrings() const {
        long long total = 0;
        for (size_t i = 1; i < st.size(); ++i) {
            int link_len = (st[i].link == -1) ? 0 : st[static_cast<size_t>(st[i].link)].len;
            total += (st[i].len - link_len);
        }
        return total;
    }

    bool contains(const string& pat) const {
        int cur = 0;
        for (char c : pat) {
            auto it = st[static_cast<size_t>(cur)].next.find(c);
            if (it == st[static_cast<size_t>(cur)].next.end()) return false;
            cur = it->second;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    SuffixAutomaton sam;
    for (char c : s) {
        sam.extend(c);
    }

    cout << "States: " << sam.state_count() << "\n";
    cout << "Transitions: " << sam.transition_count() << "\n";
    cout << "Distinct substrings: " << sam.distinct_substrings() << "\n";

    int num_queries = 0;
    if (cin >> num_queries) {
        for (int q = 0; q < num_queries; ++q) {
            string pat;
            cin >> pat;
            if (sam.contains(pat)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
