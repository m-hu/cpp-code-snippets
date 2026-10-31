
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int V,R; cin>>V>>R;
        vector<vector<int>> prem(R);
        vector<int> concl(R);
        vector<vector<int>> byprem(V);
        for(int i=0;i<R;i++){
            int k; cin>>k;
            prem[i].resize(k);
            for(int j=0;j<k;j++){cin>>prem[i][j]; byprem[prem[i][j]].push_back(i);}
            cin>>concl[i];
        }
        int q; cin>>q;
        // Forward chaining
        vector<int> count(R);
        for(int i=0;i<R;i++) count[i]=prem[i].size();
        vector<char> inferred(V,0);
        queue<int> ag;
        for(int i=0;i<R;i++) if(count[i]==0 && !inferred[concl[i]]){inferred[concl[i]]=1;ag.push(concl[i]);}
        bool fc=false;
        while(!ag.empty()&&!fc){
            int p=ag.front();ag.pop();
            if(p==q){fc=true;break;}
            for(int ri:byprem[p]){
                if(--count[ri]==0){
                    int c=concl[ri];
                    if(!inferred[c]){inferred[c]=1;ag.push(c);}
                }
            }
        }
        // Backward chaining
        vector<vector<int>> byconcl(V);
        for(int i=0;i<R;i++) byconcl[concl[i]].push_back(i);
        vector<int> isfact(V,0);
        for(int i=0;i<R;i++) if(prem[i].empty()) isfact[concl[i]]=1;
        vector<char> proved(V,0);
        vector<char> visiting(V,0);
        function<bool(int)> prove = [&](int g)->bool{
            if(proved[g]) return true;
            if(visiting[g]) return false;
            if(isfact[g]){proved[g]=1;return true;}
            visiting[g]=1;
            for(int ri:byconcl[g]){
                bool all=true;
                for(int pr:prem[ri]) if(!prove(pr)){all=false;break;}
                if(all){proved[g]=1;visiting[g]=0;return true;}
            }
            visiting[g]=0;
            return false;
        };
        bool bc=prove(q);
        cout<<"HORN FC:"<<(fc?"YES":"NO")<<" BC:"<<(bc?"YES":"NO")<<"\n";
    }
    return 0;
}
