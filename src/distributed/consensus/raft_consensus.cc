#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

enum class Role { FOLLOWER, CANDIDATE, LEADER };

struct LogEntry {
    int term;
    string command;
};

struct RaftNode {
    int id;
    Role role = Role::FOLLOWER;
    int current_term = 0;
    int voted_for = -1;
    vector<LogEntry> log;
    int commit_index = -1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n_nodes = 0, n_events = 0;
    if (!(cin >> n_nodes >> n_events)) return 0;

    vector<RaftNode> cluster(static_cast<size_t>(n_nodes));
    for (int i = 0; i < n_nodes; ++i) {
        cluster[static_cast<size_t>(i)].id = i;
    }

    int majority = n_nodes / 2 + 1;

    for (int e = 0; e < n_events; ++e) {
        string event_type;
        cin >> event_type;

        if (event_type == "START_ELECTION") {
            int candidate_id = 0;
            cin >> candidate_id;
            auto& cand = cluster[static_cast<size_t>(candidate_id)];
            cand.role = Role::CANDIDATE;
            ++cand.current_term;
            cand.voted_for = candidate_id;
            int votes = 1;

            // RequestVote RPC to all other nodes
            for (int i = 0; i < n_nodes; ++i) {
                if (i == candidate_id) continue;
                auto& peer = cluster[static_cast<size_t>(i)];
                if (peer.current_term < cand.current_term) {
                    peer.current_term = cand.current_term;
                    peer.role = Role::FOLLOWER;
                    peer.voted_for = candidate_id;
                    ++votes;
                }
            }

            if (votes >= majority) {
                cand.role = Role::LEADER;
                cout << "LEADER ELECTED: " << candidate_id << " TERM: " << cand.current_term << "\n";
            } else {
                cand.role = Role::FOLLOWER;
                cout << "ELECTION FAILED: " << candidate_id << "\n";
            }
        } else if (event_type == "APPEND_ENTRY") {
            int leader_id = 0;
            string cmd;
            cin >> leader_id >> cmd;
            auto& leader = cluster[static_cast<size_t>(leader_id)];
            if (leader.role != Role::LEADER) {
                cout << "REJECT NOT LEADER\n";
                continue;
            }

            leader.log.push_back({leader.current_term, cmd});
            int replicated = 1;

            // AppendEntries RPC to peers
            for (int i = 0; i < n_nodes; ++i) {
                if (i == leader_id) continue;
                auto& peer = cluster[static_cast<size_t>(i)];
                peer.current_term = leader.current_term;
                peer.role = Role::FOLLOWER;
                peer.log.push_back({leader.current_term, cmd});
                ++replicated;
            }

            if (replicated >= majority) {
                leader.commit_index = static_cast<int>(leader.log.size()) - 1;
                for (int i = 0; i < n_nodes; ++i) {
                    cluster[static_cast<size_t>(i)].commit_index = leader.commit_index;
                }
                cout << "COMMITTED " << cmd << " AT INDEX " << leader.commit_index << "\n";
            }
        } else if (event_type == "PRINT_STATE") {
            int node_id = 0;
            cin >> node_id;
            const auto& node = cluster[static_cast<size_t>(node_id)];
            string r_str = (node.role == Role::LEADER ? "LEADER" : (node.role == Role::CANDIDATE ? "CANDIDATE" : "FOLLOWER"));
            cout << "NODE " << node_id << " ROLE " << r_str << " TERM " << node.current_term << " COMMITTED " << node.commit_index << "\n";
        }
    }

    return 0;
}
