
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;
struct LCG{ uint64_t s; LCG(uint64_t x):s(x){}
    uint64_t next(){ s=s*6364136223846793005ULL+1442695040888963407ULL; return s; }
    int nextInt(int n){ return (int)(next()%(uint64_t)n); }
    double nextDouble(){ return (double)(next()>>11)*1.1102230246251565E-16; } };
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int S,O,N,Tl; cin>>S>>O>>N>>Tl;
        long long seed; cin>>seed;
        vector<vector<double>> tr(S,vector<double>(S)), se(S,vector<double>(O));
        for(int i=0;i<S;i++)for(int j=0;j<S;j++){double n,d;cin>>n>>d;tr[i][j]=n/d;}
        for(int i=0;i<S;i++)for(int j=0;j<O;j++){double n,d;cin>>n>>d;se[i][j]=n/d;}
        vector<int> obs(Tl);
        for(int k=0;k<Tl;k++)cin>>obs[k];
        LCG rng((uint64_t)seed);
        vector<int> parts(N);
        for(int i=0;i<N;i++)parts[i]=rng.nextInt(S);
        cout<<"PF\n";
        vector<double> cum(S+1);
        for(int k=0;k<Tl;k++){
            for(int i=0;i<N;i++){
                double u=rng.nextDouble(), c=0;
                int ns=S-1;
                for(int j=0;j<S;j++){c+=tr[parts[i]][j]; if(u<c){ns=j;break;}}
                parts[i]=ns;
            }
            vector<double> w(N);
            double tot=0;
            for(int i=0;i<N;i++){w[i]=se[parts[i]][obs[k]];tot+=w[i];}
            vector<int> np(N);
            if(tot==0){
                for(int i=0;i<N;i++)np[i]=rng.nextInt(S);
            }else{
                vector<double> cw(N+1,0);
                for(int i=0;i<N;i++)cw[i+1]=cw[i]+w[i]/tot;
                for(int i=0;i<N;i++){
                    double u=rng.nextDouble();
                    int pick=N-1;
                    for(int j=0;j<N;j++) if(u<cw[j+1]){pick=j;break;}
                    np[i]=parts[pick];
                }
            }
            parts=np;
            vector<int> hist(S,0);
            for(int x:parts)hist[x]++;
            for(int j=0;j<S;j++){if(j)cout<<' ';cout<<hist[j];}
            cout<<"\n";
        }
    }
    return 0;
}
