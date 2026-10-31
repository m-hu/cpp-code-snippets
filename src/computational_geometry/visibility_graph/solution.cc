#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;
// Visibility graph shortest path: exact integer visibility predicate
// (proper crossings + vertex pass-through midpoint tests), O(V^2)
// Dijkstra with (dist,index) order, length printed %.6f.
struct Pt{long long x,y;};
long long orient(const Pt&a,const Pt&b,const Pt&c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
bool proper_cross(const Pt&a,const Pt&b,const Pt&c,const Pt&d){
    long long o1=orient(a,b,c),o2=orient(a,b,d),o3=orient(c,d,a),o4=orient(c,d,b);
    return ((o1>0)!=(o2>0))&&o1!=0&&o2!=0&&((o3>0)!=(o4>0))&&o3!=0&&o4!=0;
}
bool on_open(const Pt&p,const Pt&a,const Pt&b){
    if(orient(a,b,p)!=0)return false;
    return (p.x-a.x)*(p.x-b.x)+(p.y-a.y)*(p.y-b.y)<0;
}
bool on_closed2(long long px,long long py,const Pt&a,const Pt&b){
    long long ax=2*a.x,ay=2*a.y,bx=2*b.x,by=2*b.y;
    if((bx-ax)*(py-ay)-(by-ay)*(px-ax)!=0)return false;
    return min(ax,bx)<=px&&px<=max(ax,bx)&&min(ay,by)<=py&&py<=max(ay,by);
}
bool pip_strict(long long X,long long Y,const vector<Pt>&P){
    int m=(int)P.size();
    for(int i=0;i<m;i++)if(on_closed2(X,Y,P[i],P[(i+1)%m]))return false;
    bool inside=false;
    for(int i=0;i<m;i++){
        long long cx=2*P[i].x,cy=2*P[i].y,dx=2*P[(i+1)%m].x,dy=2*P[(i+1)%m].y;
        if((cy>Y)!=(dy>Y)){
            bool cond;
            if(dy>cy)cond=X*(dy-cy)<cx*(dy-cy)+(dx-cx)*(Y-cy);
            else cond=X*(dy-cy)>cx*(dy-cy)+(dx-cx)*(Y-cy);
            if(cond)inside=!inside;
        }
    }
    return inside;
}
bool visible(const Pt&a,const Pt&b,const vector<vector<Pt>>&obs){
    for(auto&P:obs){
        int m=(int)P.size();
        for(int i=0;i<m;i++)if(proper_cross(a,b,P[i],P[(i+1)%m]))return false;
        for(auto&v:P){
            if(on_open(v,a,b)){
                if(pip_strict(a.x+v.x,a.y+v.y,P))return false;
                if(pip_strict(v.x+b.x,v.y+b.y,P))return false;
            }
        }
    }
    return true;
}
double ew(const Pt&a,const Pt&b){double dx=(double)(a.x-b.x),dy=(double)(a.y-b.y);return sqrt(dx*dx+dy*dy);}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<vector<Pt>>obs(n);
    for(int i=0;i<n;i++){int k;cin>>k;obs[i].resize(k);for(auto&p:obs[i])cin>>p.x>>p.y;}
    Pt s,t;cin>>s.x>>s.y>>t.x>>t.y;
    vector<Pt>pts;pts.push_back(s);pts.push_back(t);
    for(auto&P:obs)for(auto&v:P)pts.push_back(v);
    int V=(int)pts.size();
    vector<vector<int>>E;
    vector<vector<double>>W(V,vector<double>(V,-1));
    for(int i=0;i<V;i++)for(int j=i+1;j<V;j++){
        if(visible(pts[i],pts[j],obs)){E.push_back({i,j});W[i][j]=W[j][i]=ew(pts[i],pts[j]);}
    }
    cout<<E.size()<<"\n";
    for(auto&e:E)cout<<e[0]<<" "<<e[1]<<"\n";
    const double INF=numeric_limits<double>::infinity();
    vector<double>dist(V,INF);vector<int>prev(V,-1),used(V,0);
    dist[0]=0;
    for(int it=0;it<V;it++){
        int u=-1;
        for(int i=0;i<V;i++)if(!used[i]&&(u==-1||dist[i]<dist[u]))u=i;
        if(u==-1||dist[u]==INF)break;
        used[u]=1;
        if(u==1)break;
        for(int v=0;v<V;v++){
            if(W[u][v]<0||used[v])continue;
            double nd=dist[u]+W[u][v];
            if(nd<dist[v]){dist[v]=nd;prev[v]=u;}
        }
    }
    if(dist[1]==INF){cout<<"0\n\n-1\n";return 0;}
    vector<int>path;for(int c=1;c!=-1;c=prev[c])path.push_back(c);
    cout<<path.size()<<"\n";
    for(int i=(int)path.size()-1;i>=0;i--){if(i!=(int)path.size()-1)cout<<" ";cout<<path[i];}
    cout<<"\n";
    cout<<fixed<<setprecision(6)<<dist[1]<<"\n";
    return 0;
}
