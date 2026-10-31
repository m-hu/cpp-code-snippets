#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,f;
    if(!(cin>>n>>f)) return 0;
    vector<int> init(n);
    for(int i=0;i<n;i++) cin>>init[i];
    int nf;cin>>nf;
    vector<bool> faulty(n,false);
    for(int i=0;i<nf;i++){int id;cin>>id;faulty[id]=true;}
    vector<int> val=init;
    for(int ph=0;ph<f+1;ph++){
        int king=ph%n;
        vector<int> nval=val;
        for(int i=0;i<n;i++) if(!faulty[i]){
            map<int,int> cnt;
            for(int j=0;j<n;j++) if(!faulty[j]) cnt[val[j]]++;
            int maj=-1,mc=0;
            for(auto &kv:cnt) if(kv.second>mc){mc=kv.second;maj=kv.first;}
            if(mc>=n-f) nval[i]=maj;
            else if(!faulty[king]) nval[i]=val[king];
        }
        val=nval;
    }
    for(int i=0;i<n;i++) if(!faulty[i]) cout<<"P"<<i<<": "<<val[i]<<"\n";
    return 0;
}
