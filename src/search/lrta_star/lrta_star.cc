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
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int R,C; cin>>R>>C;
        vector<vector<int>> grid(R, vector<int>(C,0));
        for(int i=0;i<R;i++) for(int j=0;j<C;j++) cin>>grid[i][j];
        int sr,sc,gr,gc; cin>>sr>>sc>>gr>>gc;
        // Heuristic: Manhattan distance
        auto h_man = [&](int r,int c){ return abs(r-gr)+abs(c-gc); };
        // H table
        map<pair<int,int>, int> H;
        auto getH = [&](int r,int c)->int{
            auto it=H.find({r,c});
            if(it!=H.end()) return it->second;
            return h_man(r,c);
        };
        int dr[]={-1,1,0,0};
        int dc[]={0,0,-1,1};
        int cr=sr, cc=sc;
        int steps=0;
        const int MAX_STEPS=10000;
        vector<pair<int,int>> path;
        path.push_back({cr,cc});
        while(!(cr==gr && cc==gc) && steps < MAX_STEPS){
            // find neighbors
            vector<pair<int,int>> nbrs;
            for(int d=0;d<4;d++){
                int nr=cr+dr[d], nc=cc+dc[d];
                if(nr>=0&&nr<R&&nc>=0&&nc<C&&grid[nr][nc]==0) nbrs.push_back({nr,nc});
            }
            if(nbrs.empty()) break; // stuck
            // LRTA* update: H(s) = min_{s'} ( cost(s,s') + H(s') )
            int min_h=INT_MAX;
            for(auto &nb: nbrs) min_h=min(min_h, 1+getH(nb.first, nb.second));
            H[{cr,cc}]=min_h;
            // move to best neighbor (lowest H, tie-break by row then col)
            pair<int,int> best=nbrs[0];
            int best_h=1+getH(best.first,best.second);
            for(size_t i=1;i<nbrs.size();i++){
                int hv=1+getH(nbrs[i].first,nbrs[i].second);
                if(hv<best_h || (hv==best_h && nbrs[i]<best)){ best_h=hv; best=nbrs[i]; }
            }
            cr=best.first; cc=best.second;
            path.push_back({cr,cc});
            steps++;
        }
        cout<<steps<<"\n";
        for(size_t i=0;i<path.size();i++){
            if(i) cout<<' ';
            cout<<path[i].first<<' '<<path[i].second;
        }
        cout<<"\n";
    }
    return 0;
}
