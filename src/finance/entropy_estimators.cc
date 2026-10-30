#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <cmath>
using namespace std;
// Entropy estimators for discrete symbol sequences: plug-in histogram,
// LZ78-phrase (c*log2(n)/n) and Kontoyiannis match-length (mean of
// log2(n)/L_i over positions with a prior match, else log2(n)).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M; if(!(cin>>M)) return 0;
    vector<long long> s(M);
    for(int i=0;i<M;i++) cin>>s[i];
    map<long long,int> cnt;
    for(long long x:s) cnt[x]++;
    double plug=0;
    for(auto &p:cnt){double pr=(double)p.second/M;plug-=pr*log2(pr);}
    // LZ78: longest known prefix + one new symbol per phrase
    set<vector<long long>> dict;
    int c=0; int i=0;
    while(i<M){
        int j=i;
        while(j<M&&dict.count(vector<long long>(s.begin()+i,s.begin()+j+1))>0) j++;
        if(j>=M){ c++; break; }
        dict.insert(vector<long long>(s.begin()+i,s.begin()+j+1)); c++; i=j+1;
    }
    double lz=c*log2((double)M)/M;
    // Kontoyiannis match length over second half
    double l2n=log2((double)M), ky=0; int nk=0;
    for(int p=max(1,M/2);p<M;p++){
        int best=0;
        for(int q=0;q<p;q++){
            int L=0;
            while(p+L<M&&s[q+L]==s[p+L]) L++;
            best=max(best,L);
        }
        if(best>=1){ky+=l2n/best;nk++;}
    }
    double kyv=(nk>0?ky/nk:l2n);
    cout<<fixed<<setprecision(6);
    cout<<"PLUGIN: "<<plug<<"\n";
    cout<<"LZ: "<<lz<<"\n";
    cout<<"KY: "<<kyv<<"\n";
    return 0;
}
