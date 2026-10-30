#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Dijkstra-Scholten termination detection for diffusing computations.
// Engaged nodes send basics (deficit D++); receipt by idle node engages it
// (child of sender); receipt by engaged node returns an immediate signal.
// A node with D==0 becoming idle signals its parent (cascade); origin 0
// idle with C==0 and D==0 announces termination.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,E; if(!(cin>>n>>E)) return 0;
    vector<int> engaged(n,0), parent(n,-1), idlepend(n,0);
    vector<long long> C(n,0), D(n,0);
    engaged[0]=1;
    long long signals=0, ignored=0, term_at=-1;
    vector<string> ev(E); vector<int> a(E,0), b(E,0);
    for(int k=0;k<E;k++){cin>>ev[k]; if(ev[k]=="SEND") cin>>a[k]>>b[k]; else cin>>a[k];}
    for(int k=0;k<E;k++){
        int e=k+1;
        if(term_at>=0) break;
        if(ev[k]=="SEND"){
            int u=a[k],v=b[k];
            if(!engaged[u]){ ignored++; continue; }
            D[u]++;
            if(!engaged[v]){ engaged[v]=1; parent[v]=u; C[u]++; }
            else { D[u]--; signals++; }
        } else {
            int i=a[k];
            if(!engaged[i]) continue;
            engaged[i]=0;
            int x=i;
            while(true){
                if(D[x]>0){ idlepend[x]=1; break; }
                idlepend[x]=0;
                if(x==0){ if(C[0]==0) term_at=e; break; }
                int p=parent[x]; C[p]--; D[p]--; signals++;
                if(engaged[p]) break;
                x=p;
            }
        }
        // settle idle nodes whose deficit just cleared is handled inline:
        // signals above cascade immediately, so recheck origin wait state
        // only when origin is idle with cleared deficit (covered by loop).
    }
    cout<<"TERMINATED: ";
    if(term_at>=0) cout<<term_at<<"\n"; else cout<<"NEVER\n";
    cout<<"SIGNALS: "<<signals<<"\n";
    cout<<"IGNORED: "<<ignored<<"\n";
    return 0;
}
