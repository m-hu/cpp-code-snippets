#include <iostream>
#include <vector>
#include <map>
using namespace std;
// Turpin-Coan: multi-valued -> binary Byzantine reduction. Correct processes
// reliably broadcast values (faulty messages arrive inconsistent -> dropped);
// each correct i sets w_i=v if >=n-f matching received else NONE, and binary
// input b_i=(w_i!=NONE); ideal binary BA decides AND; decision is v iff b=1.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,f; if(!(cin>>n>>f)) return 0;
    vector<long long> v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    int k;cin>>k;
    vector<int> faulty(n,0);
    for(int j=0;j<k;j++){int x;cin>>x;faulty[x]=1;}
    vector<long long> w(n,0); vector<int> has(n,0), b(n,0);
    for(int i=0;i<n;i++){
        if(faulty[i]) continue;
        map<long long,int> cnt;
        for(int j=0;j<n;j++){ if(faulty[j]) continue; cnt[v[j]]++; }
        long long best=0; int bc=0;
        for(auto &p:cnt) if(p.second>bc){bc=p.second;best=p.first;}
        if(bc>=n-f){ w[i]=best; has[i]=1; b[i]=1; }
    }
    int band=1;
    for(int i=0;i<n;i++) if(!faulty[i]&&!b[i]) band=0;
    long long dec=0; int have=0;
    if(band){ for(int i=0;i<n;i++) if(!faulty[i]&&has[i]){dec=w[i];have=1;break;} }
    for(int i=0;i<n;i++){
        if(faulty[i]){ cout<<"P"<<i<<": FAULTY\n"; continue; }
        cout<<"P"<<i<<": w=";
        if(has[i]) cout<<w[i]; else cout<<"NONE";
        cout<<" b="<<b[i]<<"\n";
    }
    cout<<"BINARY: "<<band<<"\n";
    cout<<"DECISION: ";
    if(band&&have) cout<<dec<<"\n"; else cout<<"ABSTAIN\n";
    return 0;
}
