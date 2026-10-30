#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// FloodMax & OptFloodMax (Lynch 4.2): synchronous general-network leader
// election. R = diameter rounds; FloodMax sends on every edge every round,
// OptFloodMax only resends after the known max increases.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);}
    vector<long long> id(n);
    for(int i=0;i<n;i++) cin>>id[i];
    long long mx=id[0]; for(long long x:id) mx=max(mx,x);
    int R=0;
    for(int s=0;s<n;s++){
        vector<int> d(n,-1); queue<int> q; d[s]=0; q.push(s);
        while(!q.empty()){int u=q.front();q.pop();for(int v:adj[u]) if(d[v]<0){d[v]=d[u]+1;q.push(v);}}
        for(int x:d) if(x>R) R=x;
    }
    vector<long long> seen=id;
    long long opt=0;
    vector<int> send(n,1);
    for(int r=1;r<=R;r++){
        vector<long long> ns=seen;
        for(int i=0;i<n;i++){
            if(send[i]) opt+=(long long)adj[i].size();
            for(int nb:adj[i]) if(send[nb]) ns[i]=max(ns[i],seen[nb]);
        }
        for(int i=0;i<n;i++) send[i]=(ns[i]!=seen[i]);
        seen=ns;
    }
    cout<<"LEADER: "<<mx<<"\n";
    cout<<"ROUNDS: "<<R<<"\n";
    cout<<"FLOODMAX MESSAGES: "<<2LL*m*R<<"\n";
    cout<<"OPTFLOODMAX MESSAGES: "<<opt<<"\n";
    return 0;
}
