
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
ll G;
ll gcdll(ll a,ll b){ if(a<0)a=-a; if(b<0)b=-b; while(b){ll t=a%b;a=b;b=t;} return a==0?1:a; }
struct Fr{ ll p,q; };
Fr norm(ll p,ll q){ if(q<0){p=-p;q=-q;} ll g=gcdll(p,q); return {p/g,q/g}; }
Fr mul(Fr a,Fr b){ return norm(a.p*b.p,a.q*b.q); }
Fr add(Fr a,Fr b){ return norm(a.p*b.q+b.p*a.q,a.q*b.q); }
struct Factor{ vector<int> scope; vector<Fr> tab; };
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N; cin>>N;
        vector<vector<int>> parents(N);
        vector<vector<Fr>> cpt(N);
        for(int v=0;v<N;v++){
            int k; cin>>k;
            parents[v].resize(k);
            for(int j=0;j<k;j++)cin>>parents[v][j];
            int rows=1<<k;
            cpt[v].resize(rows);
            for(int r=0;r<rows;r++){ll n,d;cin>>n>>d;cpt[v][r]=norm(n,d);}
        }
        int q,ne; cin>>q>>ne;
        vector<int> evid(N,-1);
        for(int i=0;i<ne;i++){int e,v;cin>>e>>v;evid[e]=v;}
        vector<Factor> facs;
        for(int v=0;v<N;v++){
            vector<int> sc; sc.push_back(v);
            for(int p:parents[v]) sc.push_back(p);
            sort(sc.begin(),sc.end());
            int s=sc.size(), sz=1<<s;
            vector<Fr> tab(sz);
            for(int i=0;i<sz;i++){
                int vv=0, row=0;
                for(int j=0;j<s;j++){
                    int bit=(i>>(s-1-j))&1;
                    if(sc[j]==v) vv=bit;
                }
                int k=parents[v].size();
                for(int j=0;j<k;j++){
                    int pj=parents[v][j];
                    int pos=0; while(sc[pos]!=pj)pos++;
                    int bit=(i>>(s-1-pos))&1;
                    row|=(bit<<(k-1-j));
                }
                Fr pr=cpt[v][row];
                tab[i]= vv? pr : norm(pr.q-pr.p,pr.q);
            }
            facs.push_back({sc,tab});
        }
        // restrict evidence
        for(auto &f:facs){
            for(int e=0;e<N;e++){
                if(evid[e]<0)continue;
                int pos=-1;
                for(size_t j=0;j<f.scope.size();j++) if(f.scope[j]==e)pos=j;
                if(pos<0)continue;
                int s=f.scope.size(), sz=1<<s;
                vector<Fr> nt; vector<int> ns;
                for(size_t j=0;j<f.scope.size();j++) if((int)j!=pos) ns.push_back(f.scope[j]);
                for(int i=0;i<sz;i++){
                    int bit=(i>>(s-1-pos))&1;
                    if(bit==evid[e]) nt.push_back(f.tab[i]);
                }
                f.scope=ns; f.tab=nt;
            }
        }
        // eliminate hidden vars ascending
        for(int v=0;v<N;v++){
            if(v==q||evid[v]>=0)continue;
            vector<Factor> has, rest;
            for(auto &f:facs){
                bool c=false;
                for(int x:f.scope) if(x==v)c=true;
                if(c)has.push_back(f); else rest.push_back(f);
            }
            if(has.empty()){facs=rest;continue;}
            vector<int> sc;
            for(auto &f:has) for(int x:f.scope) if(find(sc.begin(),sc.end(),x)==sc.end()) sc.push_back(x);
            sort(sc.begin(),sc.end());
            int s=sc.size(), sz=1<<s;
            vector<Fr> tab(sz,norm(1,1));
            for(int i=0;i<sz;i++){
                Fr pr=norm(1,1);
                for(auto &f:has){
                    int idx=0;
                    for(size_t j=0;j<f.scope.size();j++){
                        int pos=0; while(sc[pos]!=f.scope[j])pos++;
                        int bit=(i>>(s-1-pos))&1;
                        idx|=(bit<<((int)f.scope.size()-1-(int)j));
                    }
                    pr=mul(pr,f.tab[idx]);
                }
                tab[i]=pr;
            }
            int pos=0; while(sc[pos]!=v)pos++;
            vector<int> ns;
            for(size_t j=0;j<sc.size();j++) if((int)j!=pos) ns.push_back(sc[j]);
            vector<Fr> nt(1<<(s-1),norm(0,1));
            for(int i=0;i<sz;i++){
                int ni=0;
                for(int j=0;j<s;j++){
                    if(j==pos)continue;
                    int bit=(i>>(s-1-j))&1;
                    ni=(ni<<1)|bit;
                }
                nt[ni]=add(nt[ni],tab[i]);
            }
            rest.push_back({ns,nt});
            facs=rest;
        }
        Fr jt=norm(0,1), jf=norm(0,1);
        {
            vector<int> sc;
            for(auto &f:facs) for(int x:f.scope) if(find(sc.begin(),sc.end(),x)==sc.end()) sc.push_back(x);
            sort(sc.begin(),sc.end());
            int sn=(int)sc.size(), szn=1<<max(sn,1);
            for(int i=0;i<szn;i++){
                Fr pr=norm(1,1);
                for(auto &f:facs){
                    int idx=0;
                    for(size_t j=0;j<f.scope.size();j++){
                        int ppos=0; while(sc[ppos]!=f.scope[j])ppos++;
                        int bit=(i>>(sn-1-ppos))&1;
                        idx|=(bit<<((int)f.scope.size()-1-(int)j));
                    }
                    pr=mul(pr,f.tab[idx]);
                }
                int ppos=0; while(ppos<sn&&sc[ppos]!=q)ppos++;
                if(ppos<sn){
                    int bit=(i>>(sn-1-ppos))&1;
                    if(bit)jt=add(jt,pr); else jf=add(jf,pr);
                }
            }
        }
        Fr ans, tot=add(jt,jf);
        if(tot.p==0) ans=norm(0,1);
        else ans=norm(jt.p*tot.q, jt.q*tot.p);
        cout<<"VE "<<ans.p<<"/"<<ans.q<<"\n";
    }
    return 0;
}
