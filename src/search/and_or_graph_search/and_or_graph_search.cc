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
// Returns set of nodes in solution if solvable, empty+false if not
// Leaf terminal success = solvable, fail = unsolvable
// AND node: all children must be solvable, solution = union
// OR node: any child solvable => solution = that child solution + this node

int N;
vector<int> type_; //0 OR,1 AND,2 SUCCESS,3 FAIL
vector<vector<int>> children_;
vector<int> memo; // -1 unknown, 0 fail, 1 success
vector<set<int>> memo_plan;

bool solve(int node, set<int>& plan){
    if(memo[node]!=-1){
        if(memo[node]==0) return false;
        plan=memo_plan[node];
        return true;
    }
    if(type_[node]==2){ // success leaf
        memo[node]=1; memo_plan[node]={node}; plan={node}; return true;
    }
    if(type_[node]==3){ // fail leaf
        memo[node]=0; return false;
    }
    if(type_[node]==1){ // AND - all must succeed
        set<int> combined; combined.insert(node);
        for(int c: children_[node]){
            set<int> sub;
            if(!solve(c, sub)){ memo[node]=0; return false; }
            for(int x: sub) combined.insert(x);
        }
        memo[node]=1; memo_plan[node]=combined; plan=combined; return true;
    }
    // OR - any
    for(int c: children_[node]){
        set<int> sub;
        if(solve(c, sub)){
            set<int> combined; combined.insert(node);
            for(int x: sub) combined.insert(x);
            memo[node]=1; memo_plan[node]=combined; plan=combined; return true;
        }
    }
    memo[node]=0; return false;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        cin>>N;
        type_.assign(N,0); children_.assign(N,{});
        for(int i=0;i<N;i++) cin>>type_[i];
        for(int i=0;i<N;i++){
            if(type_[i]==0 || type_[i]==1){
                int k; cin>>k;
                children_[i].resize(k);
                for(int j=0;j<k;j++) cin>>children_[i][j];
            }
        }
        memo.assign(N,-1); memo_plan.assign(N,{});
        set<int> plan;
        bool ok=solve(0, plan);
        if(!ok){
            cout<<"UNSOLVABLE\n";
        } else {
            cout<<"SOLVABLE "<<plan.size()<<"\n";
            bool first=true;
            for(int x: plan){ if(!first) cout<<' '; cout<<x; first=false; }
            cout<<"\n";
        }
    }
    return 0;
}
