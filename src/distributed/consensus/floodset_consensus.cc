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
    vector<set<int>> W(n);
    for(int i=0;i<n;i++) W[i].insert(init[i]);
    for(int r=0;r<f+1;r++){
        vector<set<int>> nW=W;
        for(int i=0;i<n;i++) if(!faulty[i]) for(int j=0;j<n;j++) if(!faulty[j]&&i!=j) for(int v:W[j]) nW[i].insert(v);
        W=move(nW);
    }
    for(int i=0;i<n;i++) if(!faulty[i]) cout<<"P"<<i<<": "<<*W[i].begin()<<"\n";
    return 0;
}
