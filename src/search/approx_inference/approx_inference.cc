
#include <iostream>
#include <vector>
#include <cstdio>
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
        int N; cin>>N;
        vector<vector<int>> parents(N);
        vector<vector<double>> cpt(N);
        vector<vector<int>> children(N);
        for(int v=0;v<N;v++){
            int k; cin>>k;
            parents[v].resize(k);
            for(int j=0;j<k;j++){cin>>parents[v][j];children[parents[v][j]].push_back(v);}
            int rows=1<<k;
            cpt[v].resize(rows);
            for(int r=0;r<rows;r++){double n,d;cin>>n>>d;cpt[v][r]=n/d;}
        }
        int q,ne; cin>>q>>ne;
        vector<int> evid(N,-1);
        for(int i=0;i<ne;i++){int e,v;cin>>e>>v;evid[e]=v;}
        int S; long long seed; cin>>S>>seed;
        auto prow=[&](int v,const vector<int>& asn)->double{
            int k=parents[v].size(), row=0;
            for(int j=0;j<k;j++) row|=(asn[parents[v][j]]<<(k-1-j));
            return cpt[v][row];
        };
        // Rejection sampling
        {
            LCG rng((uint64_t)seed);
            int acc=0, qt=0;
            vector<int> asn(N);
            for(int s=0;s<S;s++){
                for(int v=0;v<N;v++) asn[v]=rng.nextDouble()<prow(v,asn)?1:0;
                bool ok=true;
                for(int v=0;v<N;v++) if(evid[v]>=0&&asn[v]!=evid[v]){ok=false;break;}
                if(ok){acc++; if(asn[q]==1)qt++;}
            }
            cout<<"REJECT "<<acc<<' '<<qt<<"\n";
        }
        // Likelihood weighting
        {
            LCG rng((uint64_t)seed);
            double wt=0, wq=0;
            vector<int> asn(N);
            for(int s=0;s<S;s++){
                double w=1.0;
                for(int v=0;v<N;v++){
                    if(evid[v]>=0){ asn[v]=evid[v]; double p=prow(v,asn); w*= (evid[v]==1?p:1.0-p); }
                    else asn[v]=rng.nextDouble()<prow(v,asn)?1:0;
                }
                wt+=w; if(asn[q]==1)wq+=w;
            }
            double est=wt==0?0:wq/wt;
            char buf[64]; snprintf(buf,sizeof buf,"%.6f",est);
            cout<<"LIKELIHOOD "<<buf<<"\n";
        }
        // Gibbs
        {
            LCG rng((uint64_t)seed);
            vector<int> asn(N);
            for(int v=0;v<N;v++) asn[v]= evid[v]>=0?evid[v]:rng.nextInt(2);
            auto gibbs_prob=[&](int v)->double{
                double pt,pv;
                asn[v]=1; pt=prow(v,asn);
                for(int c:children[v]){ double p=prow(c,asn); pt*= (asn[c]==1?p:1.0-p); }
                asn[v]=0; pv=1.0-prow(v,asn);
                for(int c:children[v]){ double p=prow(c,asn); pv*= (asn[c]==1?p:1.0-p); }
                if(pt+pv==0)return asn[v]?1.0:0.0;
                return pt/(pt+pv);
            };
            for(int b=0;b<10;b++) for(int v=0;v<N;v++){
                if(evid[v]>=0)continue;
                asn[v]=rng.nextDouble()<gibbs_prob(v)?1:0;
            }
            int qt=0;
            for(int s=0;s<S;s++){
                for(int v=0;v<N;v++){
                    if(evid[v]>=0)continue;
                    asn[v]=rng.nextDouble()<gibbs_prob(v)?1:0;
                }
                if(asn[q]==1)qt++;
            }
            cout<<"GIBBS "<<qt<<' '<<S<<"\n";
        }
    }
    return 0;
}
