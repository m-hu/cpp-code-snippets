#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int next[26];
    int fail;
    int dict_link;
    vector<int> gene_ids;
    Node() : fail(0), dict_link(0) {
        fill(next, next + 26, 0);
    }
};

vector<Node> trie;
vector<int> gene_health;

void init_trie() {
    trie.clear();
    trie.emplace_back(); // root at index 0
}

void insert_gene(const string& s, int id) {
    int u = 0;
    for (char c : s) {
        int idx = c - 'a';
        if (!trie[u].next[idx]) {
            trie[u].next[idx] = trie.size();
            trie.emplace_back();
        }
        u = trie[u].next[idx];
    }
    trie[u].gene_ids.push_back(id);
}

void build_aho_corasick() {
    queue<int> q;
    for (int c = 0; c < 26; ++c) {
        if (trie[0].next[c]) {
            q.push(trie[0].next[c]);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int c = 0; c < 26; ++c) {
            int v = trie[u].next[c];
            if (v) {
                int f = trie[u].fail;
                while (f && !trie[f].next[c]) {
                    f = trie[f].fail;
                }
                trie[v].fail = trie[f].next[c];
                trie[v].dict_link = !trie[trie[v].fail].gene_ids.empty() ? trie[v].fail : trie[trie[v].fail].dict_link;
                q.push(v);
            }
        }
    }
}

long long query_strand(const string& d, int first, int last) {
    long long total = 0;
    int u = 0;
    for (char c : d) {
        int idx = c - 'a';
        while (u && !trie[u].next[idx]) {
            u = trie[u].fail;
        }
        u = trie[u].next[idx];

        for (int curr = u; curr; curr = trie[curr].dict_link) {
            for (int gid : trie[curr].gene_ids) {
                if (gid >= first && gid <= last) {
                    total += gene_health[gid];
                }
            }
        }
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    init_trie();
    vector<string> genes(n);
    for (int i = 0; i < n; ++i) {
        cin >> genes[i];
    }
    gene_health.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> gene_health[i];
        insert_gene(genes[i], i);
    }

    build_aho_corasick();

    int s;
    if (!(cin >> s)) return 0;

    long long min_health = -1;
    long long max_health = -1;

    for (int i = 0; i < s; ++i) {
        int first, last;
        string strand;
        cin >> first >> last >> strand;
        long long h = query_strand(strand, first, last);
        if (min_health == -1 || h < min_health) min_health = h;
        if (max_health == -1 || h > max_health) max_health = h;
    }

    cout << min_health << " " << max_health << "\n";
    return 0;
}
