
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;
struct LCG{ uint64_t s; LCG(uint64_t x):s(x){}
    uint64_t next(){ s=s*6364136223846793005ULL+1442695040888963407ULL; return s; }
    int nextInt(int n){ return (int)(next()%(uint64_t)n); } };
struct Node{ int stones, player, visits, wins; int moves[8]; int kids[8]; int nmoves, nkids; };
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,K,I; long long seed; cin>>N>>K>>I>>seed;
        LCG rng((uint64_t)seed);
        vector<Node> tree;
        Node root; root.stones=N; root.player=0; root.visits=0; root.wins=0;
        root.nmoves=0; root.nkids=0;
        for(int m=1;m<=K&&m<=N;m++) root.moves[root.nmoves++]=m;
        tree.push_back(root);
        for(int it=0;it<I;it++){
            // selection
            int v=0;
            vector<int> traj; traj.push_back(0);
            while(true){
                Node &nd=tree[v];
                if(nd.stones==0) break;
                if(nd.nkids<nd.nmoves){
                    int mv=nd.moves[nd.nkids];
                    Node ch; ch.stones=nd.stones-mv; ch.player=1-nd.player;
                    ch.visits=0; ch.wins=0; ch.nmoves=0; ch.nkids=0;
                    for(int m=1;m<=K&&m<=ch.stones;m++) ch.moves[ch.nmoves++]=m;
                    nd.kids[nd.nkids++]=(int)tree.size();
                    tree.push_back(ch);
                    v=(int)tree.size()-1;
                    traj.push_back(v);
                    break;
                }
                double lN=log((double)nd.visits);
                int bi=0; double bu=-1e300;
                for(int i=0;i<nd.nkids;i++){
                    Node &c=tree[nd.kids[i]];
                    double u=1.0-(double)c.wins/(double)c.visits+sqrt(2.0*lN/(double)c.visits);
                    if(u>bu){bu=u;bi=i;}
                }
                v=nd.kids[bi];
                traj.push_back(v);
            }
            // simulation
            int st=tree[v].stones, pl=tree[v].player;
            while(st>0){
                int nm=0; for(int m=1;m<=K&&m<=st;m++)nm++;
                int pick=rng.nextInt(nm);
                int mv=0; for(int m=1;m<=K&&m<=st;m++){ if(pick==0){mv=m;break;} pick--; }
                st-=mv; pl=1-pl;
            }
            int winner=1-pl;
            for(int idx:traj){ tree[idx].visits++; if(tree[idx].player==winner) tree[idx].wins++; }
        }
        Node &rt=tree[0];
        int best=rt.moves[0], bv=-1;
        for(int i=0;i<rt.nkids;i++){
            int c=rt.kids[i];
            int mv=rt.stones-tree[c].stones;
            if(tree[c].visits>bv){bv=tree[c].visits;best=mv;}
        }
        cout<<"MCTS "<<best<<" V";
        for(int i=0;i<rt.nkids;i++) cout<<' '<<tree[rt.kids[i]].visits;
        cout<<" W";
        for(int i=0;i<rt.nkids;i++) cout<<' '<<tree[rt.kids[i]].wins;
        cout<<"\n";
    }
    return 0;
}
