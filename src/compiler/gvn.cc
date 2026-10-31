#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

struct Instruction {
    string dest;
    string opcode;
    string arg1;
    string arg2;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_inst = 0;
    if (!(cin >> n_inst)) return 0;

    vector<Instruction> insts;
    for (int i = 0; i < n_inst; ++i) {
        string dest, eq, opcode;
        cin >> dest >> eq >> opcode;
        if (opcode == "CONST") {
            string val;
            cin >> val;
            insts.push_back({dest, opcode, val, ""});
        } else if (opcode == "COPY") {
            string src;
            cin >> src;
            insts.push_back({dest, opcode, src, ""});
        } else {
            string a1, a2;
            cin >> a1 >> a2;
            insts.push_back({dest, opcode, a1, a2});
        }
    }

    map<string, int> var_to_vn;
    map<int, string> vn_to_rep;
    map<tuple<string, int, int>, int> expr_to_vn;
    map<long long, int> const_to_vn;

    int next_vn = 1;
    int redundant_count = 0;

    auto get_var_vn = [&](const string& v) -> int {
        auto it = var_to_vn.find(v);
        if (it != var_to_vn.end()) {
            return it->second;
        }
        int vn = next_vn++;
        var_to_vn[v] = vn;
        vn_to_rep[vn] = v;
        return vn;
    };

    for (const auto& inst : insts) {
        if (inst.opcode == "CONST") {
            long long val = stoll(inst.arg1);
            int vn = 0;
            auto it = const_to_vn.find(val);
            if (it != const_to_vn.end()) {
                vn = it->second;
                var_to_vn[inst.dest] = vn;
                ++redundant_count;
                cout << inst.dest << " = " << vn_to_rep[vn] << " (VN" << vn << " REDUNDANT)\n";
            } else {
                vn = next_vn++;
                const_to_vn[val] = vn;
                var_to_vn[inst.dest] = vn;
                vn_to_rep[vn] = inst.dest;
                cout << inst.dest << " = CONST " << val << " (VN" << vn << ")\n";
            }
        } else if (inst.opcode == "COPY") {
            int src_vn = get_var_vn(inst.arg1);
            var_to_vn[inst.dest] = src_vn;
            ++redundant_count;
            cout << inst.dest << " = " << vn_to_rep[src_vn] << " (VN" << src_vn << " REDUNDANT)\n";
        } else if (inst.opcode == "PHI") {
            int vn1 = get_var_vn(inst.arg1);
            int vn2 = get_var_vn(inst.arg2);
            if (vn1 == vn2) {
                var_to_vn[inst.dest] = vn1;
                ++redundant_count;
                cout << inst.dest << " = " << vn_to_rep[vn1] << " (VN" << vn1 << " REDUNDANT PHI)\n";
            } else {
                // Canonicalize phi operands
                if (vn1 > vn2) swap(vn1, vn2);
                auto expr_key = make_tuple("PHI", vn1, vn2);
                auto it = expr_to_vn.find(expr_key);
                if (it != expr_to_vn.end()) {
                    int vn = it->second;
                    var_to_vn[inst.dest] = vn;
                    ++redundant_count;
                    cout << inst.dest << " = " << vn_to_rep[vn] << " (VN" << vn << " REDUNDANT)\n";
                } else {
                    int vn = next_vn++;
                    expr_to_vn[expr_key] = vn;
                    var_to_vn[inst.dest] = vn;
                    vn_to_rep[vn] = inst.dest;
                    cout << inst.dest << " = PHI VN" << vn1 << " VN" << vn2 << " (VN" << vn << ")\n";
                }
            }
        } else {
            // Binary operation: ADD, MUL, SUB, DIV
            int vn1 = get_var_vn(inst.arg1);
            int vn2 = get_var_vn(inst.arg2);
            string op = inst.opcode;

            // Commutative canonicalization
            if ((op == "ADD" || op == "MUL") && vn1 > vn2) {
                swap(vn1, vn2);
            }

            auto expr_key = make_tuple(op, vn1, vn2);
            auto it = expr_to_vn.find(expr_key);
            if (it != expr_to_vn.end()) {
                int vn = it->second;
                var_to_vn[inst.dest] = vn;
                ++redundant_count;
                cout << inst.dest << " = " << vn_to_rep[vn] << " (VN" << vn << " REDUNDANT)\n";
            } else {
                int vn = next_vn++;
                expr_to_vn[expr_key] = vn;
                var_to_vn[inst.dest] = vn;
                vn_to_rep[vn] = inst.dest;
                cout << inst.dest << " = " << op << " VN" << vn1 << " VN" << vn2 << " (VN" << vn << ")\n";
            }
        }
    }

    cout << "Total unique VNs: " << (next_vn - 1) << "\n";
    cout << "Redundant instructions eliminated: " << redundant_count << "\n";

    return 0;
}
