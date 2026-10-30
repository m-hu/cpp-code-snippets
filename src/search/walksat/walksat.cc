
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;
struct LCG{ uint64_t s; LCG(uint64_t x):s(x){}
    uint64_t next(){ s=s*6364136223846793005ULL+1442695040888963407ULL; return s; }
    int nextInt(int n){ return (int)(next()%(uint64_t)n); } };
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int V,C,MF,pn,pd; long long seed;
        cin>>V>>C>>MF>>pn>>pd>>seed;
        vector<vector<int>> clauses(C);
        for(int i=0;i<C;i++){int k;cin>>k;clauses[i].resize(k);for(int j=0;j<k;j++)cin>>clauses[i][j];}
        LCG rng((uint64_t)seed);
        vector<int> asn(V);
        for(int v=0;v<V;v++) asn[v]=rng.nextInt(2);
        auto sat_lit=[&](int l){int v=abs(l)-1; return (asn[v]==1)==(l>0);};
        auto sat_cls=[&](const vector<int>& c){for(int l:c)if(sat_lit(l))return true;return false;};
        bool solved=false;
        auto all_sat=[&]{for(auto &c:clauses)if(!sat_cls(c))return false;return true;};
        if(all_sat()) solved=true;
        for(int f=0;f<MF&&!solved;f++){
            vector<int> unsat;
            for(int i=0;i<C;i++) if(!sat_cls(clauses[i])) unsat.push_back(i);
            int ci=unsat[rng.nextInt((int)unsat.size())];
            vector<int>& cl=clauses[ci];
            int pick=-1;
            if(rng.next()%(uint64_t)pd < (uint64_t)pn){
                pick=abs(cl[rng.nextInt((int)cl.size())])-1;
            }else{
                int best=1000000000;
                for(int l:cl){
                    int v=abs(l)-1, brk=0;
                    asn[v]^=1;
                    for(auto &c2:clauses){ if(sat_cls(c2)) continue;
                        // count newly-broken: was sat before flip?
                        asn[v]^=1; bool was=sat_cls(c2); asn[v]^=1;
                        if(was) brk++;
                    }
                    asn[v]^=1;
                    if(brk<best){best=brk;pick=v;}
                }
            }
            asn[pick]^=1;
            if(all_sat()) solved=true;
        }
        cout<<"WALKSAT "<<(solved?"SAT":"UNKNOWN");
        for(int v=0;v<V;v++) cout<<' '<<asn[v];
        cout<<"\n";
    }
    return 0;
}
