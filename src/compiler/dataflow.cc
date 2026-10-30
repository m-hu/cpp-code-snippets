#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string mode; int n;
    if(!(cin>>mode>>n)) return 0;
    struct EInfo{string id,v1,v2;};
    vector<EInfo> exprs;
    map<string,int> eidx;
    if(mode=="AVAIL"){
        int ne; cin>>ne;
        for(int i=0;i<ne;i++){EInfo e; string op; cin>>e.id>>e.v1>>op>>e.v2; eidx[e.id]=exprs.size(); exprs.push_back(e);}
    }
    vector<vector<int> > succ(n);
    vector<vector<string> > defs(n), uses(n), gens(n);
    vector<string> allvars;
    for(int b=0;b<n;b++){
        int ns; cin>>ns; succ[b].resize(ns);
        for(int i=0;i<ns;i++) cin>>succ[b][i];
        int nd; cin>>nd; defs[b].resize(nd);
        for(int i=0;i<nd;i++){cin>>defs[b][i]; allvars.push_back(defs[b][i]);}
        if(mode=="AVAIL"){int ng; cin>>ng; gens[b].resize(ng); for(int i=0;i<ng;i++) cin>>gens[b][i];}
        else{int nu; cin>>nu; uses[b].resize(nu); for(int i=0;i<nu;i++){cin>>uses[b][i]; allvars.push_back(uses[b][i]);}}
    }
    vector<vector<int> > pred(n);
    for(int b=0;b<n;b++) for(int s:succ[b]) pred[s].push_back(b);
    vector<int> DEF(n,0),USE(n,0),GEN(n,0),KILL(n,0);
    int U=0;
    vector<string> names;
    if(mode=="LIVE"){
        sort(allvars.begin(),allvars.end());
        allvars.erase(unique(allvars.begin(),allvars.end()),allvars.end());
        names=allvars; U=names.size();
        map<string,int> vi; for(int i=0;i<U;i++) vi[names[i]]=i;
        for(int b=0;b<n;b++){
            for(auto &v:defs[b]) DEF[b]|=(1<<vi[v]);
            for(auto &v:uses[b]) USE[b]|=(1<<vi[v]);
        }
    }else if(mode=="REACH"){
        vector<string> dvar;
        vector<vector<int> > dids(n);
        for(int b=0;b<n;b++) for(auto &v:defs[b]){dids[b].push_back((int)dvar.size()); dvar.push_back(v);}
        U=dvar.size();
        for(int i=0;i<U;i++) names.push_back("d"+to_string(i));
        for(int b=0;b<n;b++){
            for(int id:dids[b]) GEN[b]|=(1<<id);
            for(int i=0;i<U;i++){
                bool mine=false; for(int id:dids[b]) if(id==i) mine=true;
                if(!mine) for(auto &v:defs[b]) if(v==dvar[i]) KILL[b]|=(1<<i);
            }
        }
    }else{
        U=exprs.size();
        for(auto &e:exprs) names.push_back(e.id);
        for(int b=0;b<n;b++){
            for(auto &g:gens[b]) GEN[b]|=(1<<eidx[g]);
            for(int i=0;i<U;i++)
                for(auto &v:defs[b])
                    if(v==exprs[i].v1||v==exprs[i].v2) KILL[b]|=(1<<i);
        }
    }
    int ALL=(U==0?0:((1<<U)-1));
    vector<int> IN(n,0),OUT(n,0);
    if(mode=="AVAIL") for(int b=0;b<n;b++) OUT[b]=ALL;
    int iters=0;
    if(mode=="LIVE"){
        bool ch=true;
        while(ch){ch=false;iters++;
            for(int b=n-1;b>=0;b--){
                int o=0; for(int s:succ[b]) o|=IN[s];
                int ni=(USE[b]|(o&(~DEF[b])))&ALL;
                if(o!=OUT[b]||ni!=IN[b]){OUT[b]=o;IN[b]=ni;ch=true;}
            }
        }
    }else{
        bool ch=true;
        while(ch){ch=false;iters++;
            for(int b=0;b<n;b++){
                int ni=0;
                if(mode=="REACH"){ if(b!=0) for(int p:pred[b]) ni|=OUT[p]; }
                else{
                    if(b==0) ni=0;
                    else if(pred[b].empty()) ni=ALL;
                    else{ni=ALL; for(int p:pred[b]) ni&=OUT[p];}
                }
                int no=(GEN[b]|(ni&(~KILL[b])))&ALL;
                if(ni!=IN[b]||no!=OUT[b]){IN[b]=ni;OUT[b]=no;ch=true;}
            }
        }
    }
    for(int b=0;b<n;b++){
        cout<<"B"<<b<<" IN={";
        bool f=true;
        for(int i=0;i<U;i++) if(IN[b]>>i&1){if(!f)cout<<",";cout<<names[i];f=false;}
        cout<<"} OUT={"; f=true;
        for(int i=0;i<U;i++) if(OUT[b]>>i&1){if(!f)cout<<",";cout<<names[i];f=false;}
        cout<<"}\n";
    }
    cout<<"ITERATIONS "<<iters<<"\n";
    return 0;
}
