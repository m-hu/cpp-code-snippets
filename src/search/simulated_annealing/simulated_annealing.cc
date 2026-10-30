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

int attacking_pairs(const vector<int>& b){
    int n=b.size(),cnt=0;
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
        if(b[i]==b[j]) cnt++;
        else if(abs(b[i]-b[j])==abs(i-j)) cnt++;
    }
    return cnt;
}
struct LCG{ uint64_t s; LCG(uint64_t seed):s(seed){}
    uint64_t next(){ s=s*6364136223846793005ULL+1442695040888963407ULL; return s; }
    double nextDouble(){ return (next()>>11)*0x1.0p-53; }
    int nextInt(int n){ return (int)(next()% (uint64_t)n); }
};
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N; cin>>N;
        vector<int> board(N);
        for(int i=0;i<N;i++) cin>>board[i];
        long long seed; cin>>seed;
        double temp=100.0;
        const double cooling=0.99;
        const double temp_min=0.01;
        LCG rng((uint64_t)seed);
        int cur_cost=attacking_pairs(board);
        int best_cost=cur_cost;
        vector<int> best_board=board;
        int steps=0;
        const int max_steps=5000;
        while(temp > temp_min && steps < max_steps){
            // random neighbor: move random queen to random col
            int r=rng.nextInt(N);
            int c=rng.nextInt(N);
            if(c==board[r]){
                // try to pick different
                c=(c+1)%N;
            }
            int old=board[r]; board[r]=c;
            int new_cost=attacking_pairs(board);
            int delta=new_cost - cur_cost;
            if(delta < 0 || rng.nextDouble() < exp(-(double)delta/temp)){
                cur_cost=new_cost;
                if(cur_cost < best_cost){ best_cost=cur_cost; best_board=board; }
            } else {
                board[r]=old;
            }
            temp*=cooling;
            steps++;
        }
        // output best found
        for(int i=0;i<N;i++){ if(i) cout<<' '; cout<<best_board[i]; }
        cout<<"\n"<<best_cost<<"\n";
    }
    return 0;
}
