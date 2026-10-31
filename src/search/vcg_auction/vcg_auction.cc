
#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,M,B; cin>>N>>M>>B;
        vector<int> bb(B,0),bv(B,0);
        vector<int> bmask(B,0);
        for(int i=0;i<B;i++){
            int bi,k;cin>>bi>>k;
            int m=0;
            for(int j=0;j<k;j++){int x;cin>>x;m|=1<<x;}
            int v;cin>>v;
            bb[i]=bi;bmask[i]=m;bv[i]=v;
        }
        auto welfare=[&](int skip_bidder, vector<int>* won)->int{
            int best=0, bestm=0;
            for(int m=0;m<(1<<B);m++){
                int used=0,tot=0; bool ok=true;
                for(int i=0;i<B;i++){
                    if(!(m>>i&1))continue;
                    if(skip_bidder>=0&&bb[i]==skip_bidder){ok=false;break;}
                    if(used&bmask[i]){ok=false;break;}
                    used|=bmask[i]; tot+=bv[i];
                }
                if(ok&&tot>best){best=tot;bestm=m;}
            }
            if(won){won->clear(); for(int i=0;i<B;i++)if(bestm>>i&1)won->push_back(i);}
            return best;
        };
        vector<int> won;
        int W=welfare(-1,&won);
        cout<<"VCG "<<W<<"\nPAY";
        for(int i=0;i<N;i++){
            int mine=0;
            for(int w:won)if(bb[w]==i)mine+=bv[w];
            int Wo=welfare(i,nullptr);
            cout<<' '<<(Wo-(W-mine));
        }
        cout<<"\n";
    }
    return 0;
}
