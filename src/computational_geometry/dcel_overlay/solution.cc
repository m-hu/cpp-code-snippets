#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;
// DCEL planar overlay (de Berg 2.2-2.3): exact integer overlay of two
// simple polygons in general position. Half-edges with twins, CCW
// edge order (integer angles at vertices, orientation rule at
// crossings), next-pointer face traversal. Faces = cycles-C+1.
struct Pt{long long x,y;};
long long cross(const Pt&a,const Pt&b,const Pt&c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
struct Frac{long long n,d;};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n1;if(!(cin>>n1))return 0;
    vector<Pt>p1(n1);for(int i=0;i<n1;i++)cin>>p1[i].x>>p1[i].y;
    int n2;cin>>n2;
    vector<Pt>p2(n2);for(int i=0;i<n2;i++)cin>>p2[i].x>>p2[i].y;
    auto proper=[&](Pt a,Pt b,Pt c,Pt d){
        long long d1=cross(c,d,a),d2=cross(c,d,b),d3=cross(a,b,c),d4=cross(a,b,d);
        return ((d1>0&&d2<0)||(d1<0&&d2>0))&&((d3>0&&d4<0)||(d3<0&&d4>0));
    };
    auto tparam=[](Pt a,Pt b,Pt c,Pt d){
        long long rx=b.x-a.x,ry=b.y-a.y,qx=d.x-c.x,qy=d.y-c.y;
        long long num=(c.x-a.x)*qy-(c.y-a.y)*qx,den=rx*qy-ry*qx;
        if(den<0){den=-den;num=-num;}
        return Frac{num,den};
    };
    struct Xing{int e1,e2;Frac t1,t2;};
    vector<Xing>xs;
    for(int i=0;i<n1;i++)for(int j=0;j<n2;j++){
        Pt a=p1[i],b=p1[(i+1)%n1],c=p2[j],d=p2[(j+1)%n2];
        if(proper(a,b,c,d))xs.push_back({i,j,tparam(a,b,c,d),tparam(c,d,a,b)});
    }
    int X=(int)xs.size(),V=n1+n2+X;
    auto xvid=[&](int k){return n1+n2+k;};
    vector<vector<int>>on1(n1),on2(n2);
    for(int k=0;k<X;k++){on1[xs[k].e1].push_back(k);on2[xs[k].e2].push_back(k);}
    auto flt=[](const Frac&a,const Frac&b){return a.n*b.d<b.n*a.d;};
    for(int i=0;i<n1;i++)sort(on1[i].begin(),on1[i].end(),[&](int k,int l){return flt(xs[k].t1,xs[l].t1);});
    for(int j=0;j<n2;j++)sort(on2[j].begin(),on2[j].end(),[&](int k,int l){return flt(xs[k].t2,xs[l].t2);});
    struct UE{int u,v,poly,e;};
    vector<UE>ues;
    for(int i=0;i<n1;i++){int prev=i;for(int k:on1[i]){ues.push_back({prev,xvid(k),1,i});prev=xvid(k);}ues.push_back({prev,(i+1)%n1,1,i});}
    for(int j=0;j<n2;j++){int prev=n1+j;for(int k:on2[j]){ues.push_back({prev,xvid(k),2,j});prev=xvid(k);}ues.push_back({prev,n1+(j+1)%n2,2,j});}
    int E=(int)ues.size();
    struct HE{int from,to,twin,poly,e;};
    vector<HE>hes;hes.reserve(2*E);
    for(auto&ue:ues){int k=(int)hes.size();hes.push_back({ue.u,ue.v,k+1,ue.poly,ue.e});hes.push_back({ue.v,ue.u,k,ue.poly,ue.e});}
    int H=(int)hes.size();
    vector<vector<int>>out(V);
    for(int h=0;h<H;h++)out[hes[h].from].push_back(h);
    vector<vector<int>>ccw(V);
    for(int v=0;v<n1+n2;v++){
        vector<int>hs=out[v];
        auto dirOf=[&](int h)->Pt{
            int poly=hes[h].poly,e=hes[h].e;
            if(poly==1){Pt a=p1[e],b=p1[(e+1)%n1],vv=p1[v];Pt w=(vv.x==a.x&&vv.y==a.y)?b:a;return {w.x-vv.x,w.y-vv.y};}
            int vv=v-n1;Pt a=p2[e],b=p2[(e+1)%n2],cur=p2[vv];Pt w=(cur.x==a.x&&cur.y==a.y)?b:a;return {w.x-cur.x,w.y-cur.y};
        };
        sort(hs.begin(),hs.end(),[&](int h1,int h2){
            Pt d1=dirOf(h1),d2=dirOf(h2);
            int q1=(d1.y>0||(d1.y==0&&d1.x>0))?0:1;
            int q2=(d2.y>0||(d2.y==0&&d2.x>0))?0:1;
            if(q1!=q2)return q1<q2;
            return d1.x*d2.y-d1.y*d2.x>0;
        });
        ccw[v]=hs;
    }
    for(int k=0;k<X;k++){
        int v=xvid(k),e1=xs[k].e1,e2=xs[k].e2;
        Pt a=p1[e1],b=p1[(e1+1)%n1],c=p2[e2],d=p2[(e2+1)%n2];
        vector<int>ch1;ch1.push_back(e1);for(int kk:on1[e1])ch1.push_back(xvid(kk));ch1.push_back((e1+1)%n1);
        vector<int>ch2;ch2.push_back(n1+e2);for(int kk:on2[e2])ch2.push_back(xvid(kk));ch2.push_back(n1+(e2+1)%n2);
        int i1=0;while(ch1[i1]!=v)i1++;
        int i2=0;while(ch2[i2]!=v)i2++;
        int toA=ch1[i1-1],toB=ch1[i1+1],toC=ch2[i2-1],toD=ch2[i2+1];
        int hA=-1,hB=-1,hC=-1,hD=-1;
        for(int h:out[v]){int t=hes[h].to;if(t==toA)hA=h;else if(t==toB)hB=h;else if(t==toC)hC=h;else hD=h;}
        if(cross(a,b,c)>0)ccw[v]={hB,hC,hA,hD};
        else ccw[v]={hB,hD,hA,hC};
    }
    vector<int>pos(H,-1);
    for(int v=0;v<V;v++)for(int i=0;i<(int)ccw[v].size();i++)pos[ccw[v][i]]=i;
    vector<int>nxt(H,-1);
    for(int h=0;h<H;h++){int w=hes[h].to,t=hes[h].twin,k=(int)ccw[w].size(),p=pos[t];nxt[h]=ccw[w][(p-1+k)%k];}
    vector<char>vis(H,0);
    int cycles=0;
    for(int h=0;h<H;h++)if(!vis[h]){cycles++;int c=h;while(!vis[c]){vis[c]=1;c=nxt[c];}}
    vector<int>par(V);iota(par.begin(),par.end(),0);
    function<int(int)>find=[&](int x)->int{return par[x]==x?x:par[x]=find(par[x]);};
    for(auto&ue:ues)par[find(ue.u)]=find(ue.v);
    int C=0;for(int v=0;v<V;v++)if(find(v)==v)C++;
    cout<<V<<" "<<E<<" "<<cycles-C+1<<"\n";
    return 0;
}
