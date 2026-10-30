#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Purged K-fold CV & combinatorial purged CV (AFML ch.7): folds partition
// label indices; training labels overlapping the test time-span are purged,
// plus an embargo (labels starting within E bars after test end). CPCV
// enumerates all C(P,k) test-partition combinations in lex order.
static vector<int> complement(int L,const vector<int>& test){
    vector<int> is(L,0);
    for(int x:test) is[x]=1;
    vector<int> r;
    for(int i=0;i<L;i++) if(!is[i]) r.push_back(i);
    return r;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string mode;
    if(!(cin>>mode)) return 0;
    int P,K=1,E;
    if(mode=="purged"){cin>>P>>E;}
    else{cin>>P>>K>>E;}
    int L;cin>>L;
    vector<int> t0(L),t1(L);
    for(int i=0;i<L;i++) cin>>t0[i]>>t1[i];
    // partitions of label indices into P contiguous groups
    vector<vector<int>> parts(P);
    for(int i=0;i<L;i++) parts[(long long)i*P/L].push_back(i);
    vector<vector<int>> tests;
    if(mode=="purged"){
        for(int f=0;f<P;f++) tests.push_back(parts[f]);
    } else {
        vector<int> comb(K);
        for(int i=0;i<K;i++) comb[i]=i;
        while(true){
            vector<int> t;
            for(int c:comb) for(int x:parts[c]) t.push_back(x);
            tests.push_back(t);
            int i=K-1;
            while(i>=0&&comb[i]==P-K+i) i--;
            if(i<0) break;
            comb[i]++;
            for(int j=i+1;j<K;j++) comb[j]=comb[j-1]+1;
        }
    }
    for(size_t s=0;s<tests.size();s++){
        vector<int> test=tests[s], train=complement(L,test);
        int tmin=t0[test[0]],tmax=t1[test[0]];
        for(int x:test){tmin=min(tmin,t0[x]);tmax=max(tmax,t1[x]);}
        vector<int> kept;
        for(int j:train){
            if(!(t1[j]<tmin||t0[j]>tmax)) continue; // overlap: purge
            if(t0[j]>tmax&&t0[j]<=tmax+E) continue; // embargo
            kept.push_back(j);
        }
        cout<<(mode=="purged"?"FOLD ":"SPLIT ")<<s<<": train=";
        if(kept.empty()) cout<<"-"; else for(size_t i=0;i<kept.size();i++){if(i)cout<<",";cout<<kept[i];}
        cout<<" test=";
        if(test.empty()) cout<<"-"; else for(size_t i=0;i<test.size();i++){if(i)cout<<",";cout<<test[i];}
        cout<<"\n";
    }
    return 0;
}
