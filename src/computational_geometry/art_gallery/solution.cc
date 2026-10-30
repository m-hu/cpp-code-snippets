#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
// Art gallery (de Berg 3.1): ear-clipping triangulation (first ear in
// scan order), 3-coloring by dual-tree BFS, smallest color class.
// Guards <= floor(n/3). Output: count + sorted guard indices.
struct Pt{long long x,y;};
long long cross(const Pt&a,const Pt&b,const Pt&c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<Pt>pin(n);for(int i=0;i<n;i++)cin>>pin[i].x>>pin[i].y;
    long long area2=0;
    for(int i=0;i<n;i++){Pt a=pin[i],b=pin[(i+1)%n];area2+=a.x*b.y-a.y*b.x;}
    vector<Pt>pts=pin;
    vector<int>w2o(n);
    for(int i=0;i<n;i++)w2o[i]=i;
    if(area2<0){reverse(pts.begin(),pts.end());for(int i=0;i<n;i++)w2o[i]=n-1-i;}
    vector<int>poly(n);
    for(int i=0;i<n;i++)poly[i]=i;
    vector<vector<int>>tris;
    auto convex=[&](int a,int b,int c){return cross(pts[a],pts[b],pts[c])>0;};
    auto inside=[&](Pt p,Pt a,Pt b,Pt c){
        long long c1=cross(a,b,p),c2=cross(b,c,p),c3=cross(c,a,p);
        return c1>0&&c2>0&&c3>0;
    };
    while((int)poly.size()>3){
        int m=(int)poly.size(),found=-1;
        for(int k=0;k<m;k++){
            int a=poly[(k-1+m)%m],b=poly[k],c=poly[(k+1)%m];
            if(!convex(a,b,c))continue;
            bool ok=true;
            for(int v:poly){if(v==a||v==b||v==c)continue;if(inside(pts[v],pts[a],pts[b],pts[c])){ok=false;break;}}
            if(ok){found=k;break;}
        }
        int m2=(int)poly.size();
        int a=poly[(found-1+m2)%m2],b=poly[found],c=poly[(found+1)%m2];
        tris.push_back({a,b,c});
        poly.erase(poly.begin()+found);
    }
    tris.push_back({poly[0],poly[1],poly[2]});
    map<pair<int,int>,vector<int>>emap;
    for(int t=0;t<(int)tris.size();t++){
        for(int e=0;e<3;e++){
            int u=tris[t][e],v=tris[t][(e+1)%3];
            if(u>v)swap(u,v);
            emap[{u,v}].push_back(t);
        }
    }
    vector<int>color(n,-1);
    color[tris[0][0]]=0;color[tris[0][1]]=1;color[tris[0][2]]=2;
    vector<char>vis(tris.size(),0);vis[0]=1;
    queue<int>q;q.push(0);
    while(!q.empty()){
        int t=q.front();q.pop();
        for(int e=0;e<3;e++){
            int u=tris[t][e],v=tris[t][(e+1)%3],a=u,b=v;
            if(a>b)swap(a,b);
            for(int s:emap[{a,b}])if(!vis[s]){
                vis[s]=1;
                int w=-1;
                for(int x:tris[s])if(x!=u&&x!=v)w=x;
                color[w]=3-color[u]-color[v];
                q.push(s);
            }
        }
    }
    vector<vector<int>>cls(3);
    for(int i=0;i<n;i++)cls[color[i]].push_back(i);
    for(int c=0;c<3;c++)sort(cls[c].begin(),cls[c].end());
    int best=0;
    for(int c=1;c<3;c++)if(cls[c].size()<cls[best].size()||(cls[c].size()==cls[best].size()&&cls[c]<cls[best]))best=c;
    vector<int>guards;
    for(int w:cls[best])guards.push_back(w2o[w]);
    sort(guards.begin(),guards.end());
    cout<<guards.size()<<"\n";
    for(size_t i=0;i<guards.size();i++){if(i)cout<<" ";cout<<guards[i];}
    cout<<"\n";
    return 0;
}
