#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <climits>
#include <utility>
#include <cstdint>
using namespace std;

int attacking_pairs(const vector<int>& b) {
    int n = (int)b.size(), cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (b[i] == b[j]) cnt++;
            else if (abs(b[i] - b[j]) == abs(i - j)) cnt++;
        }
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin>>T)) return 0;
    while(T--){
        int N; cin>>N;
        vector<int> board(N);
        for(int i=0;i<N;i++) cin>>board[i];
        // Steepest ascent hill climbing
        while(true){
            int cur = attacking_pairs(board);
            if(cur==0) break;
            int best_val = cur;
            int best_row=-1, best_col=-1;
            for(int r=0;r<N;r++){
                for(int c=0;c<N;c++){
                    if(c==board[r]) continue;
                    int old=board[r]; board[r]=c;
                    int v=attacking_pairs(board);
                    board[r]=old;
                    if(v < best_val){
                        best_val=v; best_row=r; best_col=c;
                    }
                }
            }
            if(best_row==-1) break; // local optimum
            board[best_row]=best_col;
        }
        for(int i=0;i<N;i++){
            if(i) cout<<' ';
            cout<<board[i];
        }
        cout<<"\n"<<attacking_pairs(board)<<"\n";
    }
    return 0;
}
