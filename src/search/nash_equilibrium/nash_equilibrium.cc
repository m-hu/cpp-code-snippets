
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
ll gcdll(ll a,ll b){ if(a<0)a=-a; if(b<0)b=-b; while(b){ll t=a%b;a=b;b=t;} return a==0?1:a; }
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int R,C; cin>>R>>C;
        vector<vector<ll>> u1(R,vector<ll>(C)),u2(R,vector<ll>(C));
        for(int i=0;i<R;i++)for(int j=0;j<C;j++)cin>>u1[i][j]>>u2[i][j];
        vector<int> rows(R,1),cols(C,1);
        bool changed=true;
        while(changed){
            changed=false;
            vector<int> nrows=rows;
            for(int i=0;i<R;i++){
                if(!rows[i])continue;
                for(int k=0;k<R;k++){
                    if(k==i||!rows[k])continue;
                    bool dom=true;
                    for(int j=0;j<C;j++){ if(!cols[j])continue; if(!(u1[k][j]>u1[i][j])){dom=false;break;} }
                    if(dom){nrows[i]=0;changed=true;break;}
                }
            }
            rows=nrows;
            vector<int> ncols=cols;
            for(int j=0;j<C;j++){
                if(!cols[j])continue;
                for(int k=0;k<C;k++){
                    if(k==j||!cols[k])continue;
                    bool dom=true;
                    for(int i=0;i<R;i++){ if(!rows[i])continue; if(!(u2[i][k]>u2[i][j])){dom=false;break;} }
                    if(dom){ncols[j]=0;changed=true;break;}
                }
            }
            cols=ncols;
        }
        vector<int> rr,cc;
        for(int i=0;i<R;i++)if(rows[i])rr.push_back(i);
        for(int j=0;j<C;j++)if(cols[j])cc.push_back(j);
        vector<pair<int,int>> pure;
        for(int i:rr)for(int j:cc){
            bool b1=true,b2=true;
            for(int k:rr)if(u1[k][j]>u1[i][j]){b1=false;break;}
            for(int k:cc)if(u2[i][k]>u2[i][j]){b2=false;break;}
            if(b1&&b2)pure.push_back({i,j});
        }
        cout<<"NASH "<<rr.size()<<' '<<cc.size()<<"\n";
        cout<<"PURE "<<pure.size();
        for(auto &e:pure)cout<<' '<<e.first<<':'<<e.second;
        cout<<"\n";
        if(rr.size()==2&&cc.size()==2){
            int a=rr[0],b=rr[1],c=cc[0],d=cc[1];
            ll pn=u2[b][d]-u2[b][c], pd=(u2[a][c]-u2[b][c])-(u2[a][d]-u2[b][d]);
            ll qn=u1[b][d]-u1[a][d], qd=(u1[a][c]-u1[a][d])-(u1[b][c]-u1[b][d]);
            bool ok = pd!=0&&qd!=0;
            if(ok){
                if(pd<0){pn=-pn;pd=-pd;}
                if(qd<0){qn=-qn;qd=-qd;}
                ll gp=gcdll(pn,pd),gq=gcdll(qn,qd);
                pn/=gp;pd/=gp;qn/=gq;qd/=gq;
                if(!(pn>0&&pn<pd&&qn>0&&qn<qd))ok=false;
            }
            if(!ok)cout<<"MIXED NONE\n";
            else cout<<"MIXED "<<pn<<'/'<<pd<<' '<<qn<<'/'<<qd<<"\n";
        } else cout<<"MIXED NONE\n";
    }
    return 0;
}
