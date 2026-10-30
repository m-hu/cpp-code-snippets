
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int P,A,N;
vector<int> pre_,add_,del_,actmask0;
vector<vector<int>> actids;
vector<vector<vector<char>>> amut;
vector<int> pmodes;
vector<vector<vector<char>>> pmut;
int initmask, goalmask;
set<long long> nogood;
vector<int> bits_of(int m){ vector<int> r; for(int p=0;p<P;p++) if(m>>p&1) r.push_back(p); return r; }
bool amutex_at(int lvl,int a,int b){
    if(a>b) swap(a,b);
    return amut[lvl][a][b];
}
vector<int> achievers(int p,int lvl){
    vector<int> r;
    for(int a:actids[lvl]) if(add_[a]>>p&1) r.push_back(a);
    return r;
}
pair<bool,vector<vector<int>>> extract(int k, vector<int> goals);
pair<bool,vector<vector<int>>> cover(int k, vector<int> unc, vector<int> chosen, int nextmask){
    if(unc.empty()){
        auto sub=extract(k-1,bits_of(nextmask));
        if(!sub.first) return {false,{}};
        sub.second.push_back(chosen);
        return {true,sub.second};
    }
    int g=unc[0];
    for(int a:achievers(g,k-1)){
        bool mx=false;
        for(int c:chosen) if(amutex_at(k-1,a,c)){mx=true;break;}
        if(mx)continue;
        vector<int> nu;
        for(int x:unc) if(!(add_[a]>>x&1)) nu.push_back(x);
        vector<int> nc=chosen; nc.push_back(a);
        auto r=cover(k,nu,nc,nextmask|pre_[a]);
        if(r.first) return r;
    }
    return {false,{}};
}
pair<bool,vector<vector<int>>> extract(int k, vector<int> goals){
    if(k==0){
        for(int g:goals) if(!(initmask>>g&1)) return {false,{}};
        return {true,{}};
    }
    int gm=0; for(int g:goals) gm|=1<<g;
    long long key=((long long)k<<32)|gm;
    if(nogood.count(key)) return {false,{}};
    auto r=cover(k,goals,{},0);
    if(!r.first) nogood.insert(key);
    return r;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        cin>>P>>A;
        N=A+P;
        pre_.assign(N,0);add_.assign(N,0);del_.assign(N,0);
        for(int i=0;i<A;i++){
            int n;cin>>n;for(int j=0;j<n;j++){int x;cin>>x;pre_[i]|=1<<x;}
            cin>>n;for(int j=0;j<n;j++){int x;cin>>x;add_[i]|=1<<x;}
            cin>>n;for(int j=0;j<n;j++){int x;cin>>x;del_[i]|=1<<x;}
        }
        for(int p=0;p<P;p++){pre_[A+p]=1<<p;add_[A+p]=1<<p;del_[A+p]=0;}
        int ni;cin>>ni;initmask=0;
        for(int j=0;j<ni;j++){int x;cin>>x;initmask|=1<<x;}
        int ng;cin>>ng;goalmask=0;
        for(int j=0;j<ng;j++){int x;cin>>x;goalmask|=1<<x;}
        actids.clear();amut.clear();pmodes.clear();pmut.clear();nogood.clear();
        pmodes.push_back(initmask);
        pmut.push_back(vector<vector<char>>(P,vector<char>(P,0)));
        bool solved=false; vector<vector<int>> plan; int solvedL=0;
        for(int L=0;L<=12&&!solved;L++){
            // check goals at prop level L
            if((pmodes[L]&goalmask)==goalmask){
                bool mOK=true;
                vector<int> gs=bits_of(goalmask);
                for(size_t i=0;i<gs.size()&&mOK;i++)for(size_t j=i+1;j<gs.size();j++)
                    if(pmut[L][gs[i]][gs[j]]){mOK=false;break;}
                if(mOK){
                    auto r=extract(L,gs);
                    if(r.first){solved=true;plan=r.second;solvedL=L;break;}
                }
            }
            if(L==12)break;
            // build action level L
            vector<int> aids;
            for(int a=0;a<N;a++) if((pre_[a]&~pmodes[L])==0) aids.push_back(a);
            vector<vector<char>> am(N,vector<char>(N,0));
            for(size_t i=0;i<aids.size();i++)for(size_t j=i+1;j<aids.size();j++){
                int a=aids[i],b=aids[j]; bool mx=false;
                if((add_[a]&del_[b])||(add_[b]&del_[a])) mx=true;
                if((del_[a]&pre_[b])||(del_[b]&pre_[a])) mx=true;
                if(!mx){
                    vector<int> pa=bits_of(pre_[a]),pb=bits_of(pre_[b]);
                    for(int x:pa)for(int y:pb) if(pmut[L][x][y]){mx=true;break;}
                }
                am[a][b]=am[b][a]=mx;
            }
            actids.push_back(aids); amut.push_back(am);
            int nmask=0;
            for(int a:aids) nmask|=add_[a];
            vector<vector<char>> pm(P,vector<char>(P,0));
            int mc=0;
            for(int x=0;x<P;x++)for(int y=x+1;y<P;y++){
                if(!(nmask>>x&1)&&!(nmask>>y&1)) continue;
                if(!(nmask>>x&1)||!(nmask>>y&1)) continue;
                bool mx=true;
                for(int a:aids){ if(!(add_[a]>>x&1))continue;
                    for(int b:aids){ if(!(add_[b]>>y&1))continue;
                        if(a==b||!am[a][b]){mx=false;break;} }
                    if(!mx)break; }
                pm[x][y]=pm[y][x]=mx;
                if(mx)mc++;
            }
            int prevmc=0;
            for(int x=0;x<P;x++)for(int y=x+1;y<P;y++) if(pmut[L][x][y])prevmc++;
            pmodes.push_back(nmask); pmut.push_back(pm);
            if(nmask==pmodes[L]&&mc==prevmc) break;
        }
        if(!solved){cout<<"GRAPHPLAN FAIL\n";}
        else{
            cout<<"GRAPHPLAN "<<solvedL<<"\n";
            for(int l=0;l<solvedL;l++){
                vector<int> ra;
                for(int a:plan[l]) if(a<A) ra.push_back(a);
                sort(ra.begin(),ra.end());
                for(size_t i=0;i<ra.size();i++){if(i)cout<<' ';cout<<ra[i];}
                cout<<"\n";
            }
        }
    }
    return 0;
}
