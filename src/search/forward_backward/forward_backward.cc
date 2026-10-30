
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int S,O,Tl; cin>>S>>O>>Tl;
        vector<double> pi(S);
        for(int i=0;i<S;i++){double n,d;cin>>n>>d;pi[i]=n/d;}
        vector<vector<double>> A(S,vector<double>(S)),B(S,vector<double>(O));
        for(int i=0;i<S;i++)for(int j=0;j<S;j++){double n,d;cin>>n>>d;A[i][j]=n/d;}
        for(int i=0;i<S;i++)for(int j=0;j<O;j++){double n,d;cin>>n>>d;B[i][j]=n/d;}
        vector<int> obs(Tl);
        for(int k=0;k<Tl;k++)cin>>obs[k];
        vector<vector<double>> al(Tl,vector<double>(S)),be(Tl,vector<double>(S));
        for(int i=0;i<S;i++)al[0][i]=pi[i]*B[i][obs[0]];
        for(int k=1;k<Tl;k++)for(int j=0;j<S;j++){
            double s=0;
            for(int i=0;i<S;i++)s+=al[k-1][i]*A[i][j];
            al[k][j]=s*B[j][obs[k]];
        }
        for(int i=0;i<S;i++)be[Tl-1][i]=1.0;
        for(int k=Tl-2;k>=0;k--)for(int i=0;i<S;i++){
            double s=0;
            for(int j=0;j<S;j++)s+=A[i][j]*B[j][obs[k+1]]*be[k+1][j];
            be[k][i]=s;
        }
        cout<<"FB\n";
        for(int k=0;k<Tl;k++){
            double tot=0;
            for(int i=0;i<S;i++)tot+=al[k][i]*be[k][i];
            for(int i=0;i<S;i++){
                if(i)cout<<' ';
                double g=tot==0?0:al[k][i]*be[k][i]/tot;
                char buf[32];snprintf(buf,sizeof buf,"%.6f",g);
                cout<<buf;
            }
            cout<<"\n";
        }
    }
    return 0;
}
