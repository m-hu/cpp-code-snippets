#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Afek-Attiya-Dolev-Gafni-Merritt-Shavit wait-free atomic snapshot (essence):
// update writes a component; scan double-collects with concurrent updates
// applied between collects; on mismatch the fresh view is borrowed.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q; if(!(cin>>n>>q)) return 0;
    vector<long long> state(n,0);
    int sn=0;
    for(int k=0;k<q;k++){
        string op;cin>>op;
        if(op=="U"){ int i;long long v;cin>>i>>v;state[i]=v; }
        else{
            int c;cin>>c;
            vector<long long> c1=state;
            for(int j=0;j<c;j++){int u;long long v;cin>>u>>v;state[u]=v;}
            vector<long long> c2=state;
            int collects=(c1==c2?2:3);
            cout<<"SCAN "<<sn<<":";
            for(long long x:c2) cout<<" "<<x;
            cout<<" collects="<<collects<<"\n";
            sn++;
        }
    }
    cout<<"STATE:";
    for(long long x:state) cout<<" "<<x;
    cout<<"\n";
    return 0;
}
