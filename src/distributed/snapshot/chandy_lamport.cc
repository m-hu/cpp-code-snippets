#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct Message {
    int from;
    int to;
    string text; // "MARKER" or normal message
};

struct Process {
    int id;
    int balance = 0;
    bool recorded = false;
    int recorded_balance = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_procs = 0, n_events = 0;
    if (!(cin >> n_procs >> n_events)) return 0;

    vector<Process> procs(static_cast<size_t>(n_procs));
    for (int i = 0; i < n_procs; ++i) {
        procs[static_cast<size_t>(i)].id = i;
        cin >> procs[static_cast<size_t>(i)].balance;
    }

    // Channels: channel[u][v] = queue of messages
    vector<vector<queue<Message>>> channels(static_cast<size_t>(n_procs), vector<queue<Message>>(static_cast<size_t>(n_procs)));
    // Recorded channel messages: recorded_channel[u][v] = vector<string>
    vector<vector<vector<string>>> recorded_channels(static_cast<size_t>(n_procs), vector<vector<string>>(static_cast<size_t>(n_procs)));
    // Recording channel state flags: recording[u][v] (recording incoming messages from u to v)
    vector<vector<bool>> is_recording(static_cast<size_t>(n_procs), vector<bool>(static_cast<size_t>(n_procs), false));

    for (int e = 0; e < n_events; ++e) {
        string event_type;
        cin >> event_type;

        if (event_type == "TRANSFER") {
            int u = 0, v = 0, amt = 0;
            cin >> u >> v >> amt;
            procs[static_cast<size_t>(u)].balance -= amt;
            channels[static_cast<size_t>(u)][static_cast<size_t>(v)].push({u, v, to_string(amt)});
        } else if (event_type == "RECEIVE") {
            int u = 0, v = 0;
            cin >> u >> v;
            if (!channels[static_cast<size_t>(u)][static_cast<size_t>(v)].empty()) {
                Message msg = channels[static_cast<size_t>(u)][static_cast<size_t>(v)].front();
                channels[static_cast<size_t>(u)][static_cast<size_t>(v)].pop();

                if (msg.text == "MARKER") {
                    if (!procs[static_cast<size_t>(v)].recorded) {
                        procs[static_cast<size_t>(v)].recorded = true;
                        procs[static_cast<size_t>(v)].recorded_balance = procs[static_cast<size_t>(v)].balance;
                        // Turn on recording for all other incoming channels
                        for (int k = 0; k < n_procs; ++k) {
                            if (k != v && k != u) is_recording[static_cast<size_t>(k)][static_cast<size_t>(v)] = true;
                        }
                        // Send marker along all outgoing channels
                        for (int k = 0; k < n_procs; ++k) {
                            if (k != v) channels[static_cast<size_t>(v)][static_cast<size_t>(k)].push({v, k, "MARKER"});
                        }
                    } else {
                        // Stop recording channel u -> v
                        is_recording[static_cast<size_t>(u)][static_cast<size_t>(v)] = false;
                    }
                } else {
                    int amt = stoi(msg.text);
                    procs[static_cast<size_t>(v)].balance += amt;
                    if (is_recording[static_cast<size_t>(u)][static_cast<size_t>(v)]) {
                        recorded_channels[static_cast<size_t>(u)][static_cast<size_t>(v)].push_back(msg.text);
                    }
                }
            }
        } else if (event_type == "SNAPSHOT_INIT") {
            int init_p = 0;
            cin >> init_p;
            if (!procs[static_cast<size_t>(init_p)].recorded) {
                procs[static_cast<size_t>(init_p)].recorded = true;
                procs[static_cast<size_t>(init_p)].recorded_balance = procs[static_cast<size_t>(init_p)].balance;
                for (int k = 0; k < n_procs; ++k) {
                    if (k != init_p) {
                        is_recording[static_cast<size_t>(k)][static_cast<size_t>(init_p)] = true;
                        channels[static_cast<size_t>(init_p)][static_cast<size_t>(k)].push({init_p, k, "MARKER"});
                    }
                }
            }
        }
    }

    // Output recorded snapshot
    int total_snapshot_money = 0;
    for (int i = 0; i < n_procs; ++i) {
        cout << "P" << i << ": " << procs[static_cast<size_t>(i)].recorded_balance << "\n";
        total_snapshot_money += procs[static_cast<size_t>(i)].recorded_balance;
    }

    for (int u = 0; u < n_procs; ++u) {
        for (int v = 0; v < n_procs; ++v) {
            for (const auto& msg_text : recorded_channels[static_cast<size_t>(u)][static_cast<size_t>(v)]) {
                cout << "CHANNEL " << u << "->" << v << ": " << msg_text << "\n";
                total_snapshot_money += stoi(msg_text);
            }
        }
    }
    cout << "TOTAL: " << total_snapshot_money << "\n";

    return 0;
}
