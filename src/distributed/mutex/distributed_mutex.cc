#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// Distributed mutual exclusion, two protocols (mode token first):
// ra: Ricart-Agrawala — requests carry Lamport timestamps (round number);
//   grants in (ts,id) order; each entry costs 2(n-1) messages (req+reply).
// sk: Suzuki-Kasami token-based — requests served FIFO from token queue;
//   each grant costs (n-1) broadcasts + 1 token transfer (0 if holder).
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string mode; int n;
    if(!(cin>>mode>>n)) return 0;
    if(mode=="ra"){
        int R;cin>>R;
        vector<int> order;
        for(int r=0;r<R;r++){
            int c;cin>>c;
            vector<int> g(c);
            for(int j=0;j<c;j++) cin>>g[j];
            sort(g.begin(),g.end());
            for(int x:g) order.push_back(x);
        }
        cout<<"ORDER:";
        for(int x:order) cout<<" "<<x;
        cout<<"\nMSGS: "<<2LL*(n-1)*(long long)order.size()<<"\n";
    } else {
        int holder;cin>>holder;
        int Q;cin>>Q;
        vector<int> req(Q);
        for(int j=0;j<Q;j++) cin>>req[j];
        vector<int> order;
        vector<long long> ln(n,0);
        vector<vector<long long>> rn(n,vector<long long>(n,0));
        vector<int> queue;
        size_t qhead=0;
        long long hops=0;
        for(int iq=0;iq<Q;iq++){
            int i=req[iq];
            rn[i][i]++;
            for(int t=0;t<n;t++) rn[t][i]=rn[i][i]; // broadcast
            if(i==holder){ order.push_back(i); ln[i]=rn[i][i]; continue; }
            queue.push_back(i);
            while(qhead<queue.size()){
                int j=queue[qhead++];
                if(rn[holder][j]<=ln[j]) continue; // stale
                ln[j]=rn[holder][j];
                for(int t=0;t<n;t++) rn[j][t]=max(rn[j][t],rn[holder][t]);
                holder=j; hops++;
                order.push_back(j);
            }
        }
        cout<<"ORDER:";
        for(int x:order) cout<<" "<<x;
        cout<<"\nHOPS: "<<hops<<"\n";
        cout<<"MSGS: "<<(long long)(n-1)*Q+hops<<"\n";
    }
    return 0;
}
