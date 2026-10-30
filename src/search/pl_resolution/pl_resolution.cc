
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> norm_clause(vector<int> c){
    sort(c.begin(),c.end());
    c.erase(unique(c.begin(),c.end()),c.end());
    return c;
}
bool taut(const vector<int>& c){
    for(size_t i=0;i<c.size();i++)for(size_t j=0;j<c.size();j++)if(c[i]==-c[j])return true;
    return false;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int V,C; cin>>V>>C;
        vector<vector<int>> clauses;
        for(int i=0;i<C;i++){int k;cin>>k;vector<int>c(k);for(int j=0;j<k;j++)cin>>c[j];
            c=norm_clause(c); if(!taut(c)) clauses.push_back(c);}
        int q; cin>>q;
        vector<int> nq; nq.push_back(-q);
        bool has=false;
        for(auto &c:clauses) if(c==nq) has=true;
        if(!has) clauses.push_back(nq);
        bool entailed=false;
        for(int round=0; round<500 && !entailed; round++){
            vector<vector<int>> added;
            size_t n=clauses.size();
            for(size_t i=0;i<n&&!entailed;i++) for(size_t j=i+1;j<n&&!entailed;j++){
                for(size_t a=0;a<clauses[i].size()&&!entailed;a++){
                    for(size_t b=0;b<clauses[j].size()&&!entailed;b++){
                        int l1=clauses[i][a], l2=clauses[j][b];
                        if(l1!=-l2) continue;
                        vector<int> r;
                        for(int l:clauses[i]) if(l!=l1) r.push_back(l);
                        for(int l:clauses[j]) if(l!=l2) r.push_back(l);
                        r=norm_clause(r);
                        if(r.empty()){entailed=true;break;}
                        if(taut(r)) continue;
                        bool dup=false;
                        for(auto &c:clauses) if(c==r){dup=true;break;}
                        if(!dup) for(auto &c:added) if(c==r){dup=true;break;}
                        if(!dup) added.push_back(r);
                    }
                }
            }
            if(added.empty()) break;
            for(auto &c:added) clauses.push_back(c);
            if(clauses.size()>4000) break;
        }
        cout<<(entailed?"RESOLUTION ENTAILED\n":"RESOLUTION NOT-ENTAILED\n");
    }
    return 0;
}
