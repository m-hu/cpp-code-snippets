
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N,F,k; cin>>N>>F>>k;
        vector<vector<int>> X(N,vector<int>(F));
        vector<int> Y(N);
        for(int i=0;i<N;i++){for(int f=0;f<F;f++)cin>>X[i][f];cin>>Y[i];}
        int M;cin>>M;
        vector<vector<int>> Z(M,vector<int>(F));
        for(int i=0;i<M;i++)for(int f=0;f<F;f++)cin>>Z[i][f];
        cout<<"KNN";
        for(int t=0;t<M;t++){
            vector<pair<long long,int>> d;
            for(int i=0;i<N;i++){
                long long s=0;
                for(int f=0;f<F;f++){long long dd=(long long)Z[t][f]-X[i][f];s+=dd*dd;}
                d.push_back({s,i});
            }
            sort(d.begin(),d.end());
            map<int,int> votes;
            for(int j=0;j<k&&j<N;j++)votes[Y[d[j].second]]++;
            int bl=-1,bc=-1;
            for(auto &kv:votes)if(kv.second>bc){bc=kv.second;bl=kv.first;}
            cout<<' '<<bl;
        }
        cout<<"\nNB";
        vector<int> classes=Y;
        sort(classes.begin(),classes.end());
        classes.erase(unique(classes.begin(),classes.end()),classes.end());
        vector<int> vmax(F,0);
        for(int f=0;f<F;f++)for(int i=0;i<N;i++)vmax[f]=max(vmax[f],X[i][f]);
        for(int t=0;t<M;t++){
            int bl=classes[0]; double bs=-1e300;
            for(int c:classes){
                int cc=0;
                for(int i=0;i<N;i++)if(Y[i]==c)cc++;
                double s=log((double)cc/N);
                for(int f=0;f<F;f++){
                    int cnt=0;
                    for(int i=0;i<N;i++)if(Y[i]==c&&X[i][f]==Z[t][f])cnt++;
                    s+=log((double)(cnt+1)/(cc+vmax[f]+1));
                }
                if(s>bs+1e-12){bs=s;bl=c;}
            }
            cout<<' '<<bl;
        }
        cout<<"\n";
    }
    return 0;
}
