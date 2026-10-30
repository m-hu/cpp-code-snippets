#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Acceptor {
    int id;
    int promised_n = 0;
    int accepted_n = 0;
    string accepted_val = "";
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_acceptors = 0, n_ops = 0;
    if (!(cin >> n_acceptors >> n_ops)) return 0;

    vector<Acceptor> acceptors(static_cast<size_t>(n_acceptors));
    for (int i = 0; i < n_acceptors; ++i) {
        acceptors[static_cast<size_t>(i)].id = i;
    }

    int majority = n_acceptors / 2 + 1;

    for (int op_idx = 0; op_idx < n_ops; ++op_idx) {
        string op;
        cin >> op;

        if (op == "PREPARE") {
            int n_prop = 0;
            cin >> n_prop;

            int promises = 0;
            int max_acc_n = 0;
            string val_for_max = "";

            for (auto& acc : acceptors) {
                if (n_prop > acc.promised_n) {
                    acc.promised_n = n_prop;
                    ++promises;
                    if (acc.accepted_n > max_acc_n) {
                        max_acc_n = acc.accepted_n;
                        val_for_max = acc.accepted_val;
                    }
                }
            }

            if (promises >= majority) {
                if (max_acc_n > 0) {
                    cout << "PROMISED " << n_prop << " PREV " << max_acc_n << " " << val_for_max << "\n";
                } else {
                    cout << "PROMISED " << n_prop << " NONE\n";
                }
            } else {
                cout << "PREPARE REJECTED " << n_prop << "\n";
            }
        } else if (op == "PROPOSE") {
            int n_prop = 0;
            string val;
            cin >> n_prop >> val;

            int accepted_cnt = 0;
            for (auto& acc : acceptors) {
                if (n_prop >= acc.promised_n) {
                    acc.promised_n = n_prop;
                    acc.accepted_n = n_prop;
                    acc.accepted_val = val;
                    ++accepted_cnt;
                }
            }

            if (accepted_cnt >= majority) {
                cout << "CHOSEN " << n_prop << " " << val << "\n";
            } else {
                cout << "PROPOSE REJECTED " << n_prop << "\n";
            }
        }
    }

    return 0;
}
