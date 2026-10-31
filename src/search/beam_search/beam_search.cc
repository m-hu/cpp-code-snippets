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
int attacking(const vector<int>& b){ int n=b.size(),c=0; for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){ if(b[i]==b[j]) c++; else if(abs(b[i]-b[j])==abs(i-j)) c++; } return c; }
struct LCG{ uint64_t s; LCG(uint64_t x):s(x){} uint64_t next(){ s=s*6364136223846793005ULL+1442695040888963407ULL; return s; } int nextInt(int n){ return int(next()% (uint64_t)n); } };
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,k; cin>>N>>k;
        long long seed; cin>>seed;
        LCG rng(seed);
        // generate k initial boards
        vector<vector<int>> beam;
        for(int i=0;i<k;i++){ vector<int> b(N); for(int j=0;j<N;j++) b[j]=rng.nextInt(N); beam.push_back(b); }
        int best_cost=INT_MAX; vector<int> best_board;
        for(auto &b: beam){ int c=attacking(b); if(c<best_cost){best_cost=c; best_board=b;} }
        if(best_cost==0){ /* output immediately below */ } else {
            for(int iter=0; iter<100; iter++){
                // generate all successors
                vector<pair<int,vector<int>>> succs;
                for(auto &b: beam){
                    for(int r=0;r<N;r++) for(int c2=0;c2<N;c2++){
                        if(c2==b[r]) continue;
                        vector<int> nb=b; nb[r]=c2;
                        succs.push_back({attacking(nb), nb});
                    }
                }
                sort(succs.begin(), succs.end(), [](auto &a, auto &b){
                    if(a.first!=b.first) return a.first<b.first;
                    return a.second<b.second;
                });
                // keep top k unique
                vector<vector<int>> new_beam;
                for(auto &p: succs){
                    bool dup=false;
                    for(auto &ex: new_beam) if(ex==p.second) dup=true;
                    if(!dup) new_beam.push_back(p.second);
                    if((int)new_beam.size()>=k) break;
                }
                beam=new_beam;
                for(auto &b: beam){ int c=attacking(b); if(c<best_cost){best_cost=c; best_board=b;} }
                if(best_cost==0) break;
            }
        }
        for(int i=0;i<N;i++){ if(i) cout<<' '; cout<<best_board[i]; } cout<<"\n"<<best_cost<<"\n";
    }
    return 0;
}
