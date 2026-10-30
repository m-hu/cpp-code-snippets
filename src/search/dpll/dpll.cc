
#include <iostream>
#include <vector>
using namespace std;
int V;
vector<vector<int>> clauses;
bool dpll(vector<int>& asn){
    while(true){
        bool changed=false;
        // unit propagation
        for(auto &c:clauses){
            int un=0, ulit=0; bool sat=false;
            for(int l:c){
                int v=abs(l)-1;
                if(asn[v]==-1){un++;ulit=l;}
                else if((asn[v]==1)==(l>0)){sat=true;break;}
            }
            if(sat) continue;
            if(un==0) return false;
            if(un==1){
                int v=abs(ulit)-1, val=ulit>0?1:0;
                if(asn[v]==-1){asn[v]=val;changed=true;}
                else if(asn[v]!=val) return false;
            }
        }
        // pure literals
        vector<int> pos(V,0),neg(V,0);
        for(auto &c:clauses){
            bool sat=false;
            for(int l:c){int v=abs(l)-1; if(asn[v]!=-1&&(asn[v]==1)==(l>0)){sat=true;break;}}
            if(sat)continue;
            for(int l:c){int v=abs(l)-1; if(asn[v]==-1){if(l>0)pos[v]=1;else neg[v]=1;}}
        }
        for(int v=0;v<V;v++){
            if(asn[v]==-1){
                if(pos[v]&&!neg[v]){asn[v]=1;changed=true;}
                else if(neg[v]&&!pos[v]){asn[v]=0;changed=true;}
            }
        }
        if(!changed)break;
    }
    // check satisfied / find branch var
    int br=-1;
    for(auto &c:clauses){
        bool sat=false; int un=0;
        for(int l:c){int v=abs(l)-1;
            if(asn[v]==-1)un++;
            else if((asn[v]==1)==(l>0)){sat=true;break;}}
        if(!sat&&un==0)return false;
        if(!sat&&br<0){for(int l:c){int v=abs(l)-1;if(asn[v]==-1){br=v;break;}}}
    }
    // smallest unassigned overall
    for(int v=0;v<V;v++) if(asn[v]==-1){br=v;break;}
    if(br<0) return true;
    vector<int> a2=asn; a2[br]=1;
    if(dpll(a2)){asn=a2;return true;}
    a2=asn; a2[br]=0;
    if(dpll(a2)){asn=a2;return true;}
    return false;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int C; cin>>V>>C;
        clauses.assign(C,{});
        for(int i=0;i<C;i++){int k;cin>>k;clauses[i].resize(k);for(int j=0;j<k;j++)cin>>clauses[i][j];}
        vector<int> asn(V,-1);
        bool sat=dpll(asn);
        if(!sat){cout<<"DPLL UNSAT\n";}
        else{
            cout<<"DPLL SAT";
            for(int v=0;v<V;v++) cout<<' '<<(asn[v]==-1?0:asn[v]);
            cout<<"\n";
        }
    }
    return 0;
}
