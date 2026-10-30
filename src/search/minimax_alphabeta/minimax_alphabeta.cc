
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> leaves;
int full_cnt, ab_cnt;
int mm_full(int idx, int depth, bool ismax){
    if(depth==0){ full_cnt++; return leaves[idx]; }
    int a = mm_full(idx*2, depth-1, !ismax);
    int b = mm_full(idx*2+1, depth-1, !ismax);
    return ismax ? max(a,b) : min(a,b);
}
int mm_ab(int idx, int depth, bool ismax, int alpha, int beta){
    if(depth==0){ ab_cnt++; return leaves[idx]; }
    if(ismax){
        int v = -2000000000;
        v = max(v, mm_ab(idx*2, depth-1, false, alpha, beta));
        alpha = max(alpha, v);
        if(alpha >= beta) return v;
        v = max(v, mm_ab(idx*2+1, depth-1, false, alpha, beta));
        return v;
    } else {
        int v = 2000000000;
        v = min(v, mm_ab(idx*2, depth-1, true, alpha, beta));
        beta = min(beta, v);
        if(alpha >= beta) return v;
        v = min(v, mm_ab(idx*2+1, depth-1, true, alpha, beta));
        return v;
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int D; cin>>D;
        int n = 1<<D;
        leaves.assign(n,0);
        for(int i=0;i<n;i++) cin>>leaves[i];
        full_cnt=0; int v1 = mm_full(0,D,true);
        ab_cnt=0; int v2 = mm_ab(0,D,true,-2000000000,2000000000);
        cout<<"MINIMAX "<<v1<<" FULL "<<full_cnt<<" AB "<<ab_cnt<<"\n";
    }
    return 0;
}
