#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>
using namespace std;
// Randomized incremental 3D convex hull (de Berg 11.2, naive conflict).
// Fixed-seed shuffle; visible facets removed per point; horizon cone
// rebuilt; new facets oriented against a known interior point. Exact
// integer orientation; general position (no 3 collinear, no 4 coplanar).
struct Pt{long long x,y,z;};
long long orient3(const Pt&a,const Pt&b,const Pt&c,const Pt&d){
    long long abx=b.x-a.x,aby=b.y-a.y,abz=b.z-a.z;
    long long acx=c.x-a.x,acy=c.y-a.y,acz=c.z-a.z;
    long long adx=d.x-a.x,ady=d.y-a.y,adz=d.z-a.z;
    long long cx=aby*acz-abz*acy, cy=abz*acx-abx*acz, cz=abx*acy-aby*acx;
    return cx*adx+cy*ady+cz*adz;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<Pt>pts(n);
    for(int i=0;i<n;i++)cin>>pts[i].x>>pts[i].y>>pts[i].z;
    vector<int>ord(n);
    for(int i=0;i<n;i++)ord[i]=i;
    uint64_t st=199;
    for(int i=n-1;i>0;i--){st=st*6364136223846793005ULL+1442695040888963407ULL;int j=(int)((st>>33)%(uint64_t)(i+1));swap(ord[i],ord[j]);}
    // Initial tetrahedron from first 4 (general position).
    int p0=ord[0],p1=ord[1],p2=ord[2],p3=ord[3];
    struct F{int a,b,c;};
    vector<F>facets;
    int t[4]={p0,p1,p2,p3};
    for(int skip=0;skip<4;skip++){
        int v[3],k=0;
        for(int i=0;i<4;i++)if(i!=skip)v[k++]=t[i];
        // orient (v0,v1,v2) so t[skip] is below: orient3(v0,v1,v2,t[skip])<0
        if(orient3(pts[v[0]],pts[v[1]],pts[v[2]],pts[t[skip]])>0)swap(v[1],v[2]);
        facets.push_back({v[0],v[1],v[2]});
    }
    auto orientInner=[&](int a,int b,int c)->long long{
        // orient3(a,b,c,inner) with inner=inner4/4: sign(orient3(a,b,c,inner4 - 3a... use linearity:
        // orient(a,b,c,(p0+p1+p2+p3)/4): 4*orient = orient(a,b,c,p0)+...+orient(a,b,c,p3)? No: orient is linear in 4th arg only as det with (d-a): det(ab,ac,ad). ad for average = avg(d_i - a). So orient(avg) = avg(orient(d_i)). Sign = sign of sum.
        return orient3(pts[a],pts[b],pts[c],pts[p0])+orient3(pts[a],pts[b],pts[c],pts[p1])+orient3(pts[a],pts[b],pts[c],pts[p2])+orient3(pts[a],pts[b],pts[c],pts[p3]);
    };
    for(int oi=4;oi<n;oi++){
        int p=ord[oi];
        vector<int>vis;
        for(int f=0;f<(int)facets.size();f++){
            F&fc=facets[f];
            if(orient3(pts[fc.a],pts[fc.b],pts[fc.c],pts[p])>0)vis.push_back(f);
        }
        if(vis.empty())continue;
        vector<char>isvis(facets.size(),0);
        for(int f:vis)isvis[f]=1;
        map<pair<int,int>,int>ecount;
        for(int f:vis){
            F&fc=facets[f];
            int vs[3]={fc.a,fc.b,fc.c};
            for(int e=0;e<3;e++){
                int u=vs[e],v=vs[(e+1)%3];
                if(u>v)swap(u,v);
                ecount[{u,v}]++;
            }
        }
        vector<F>nf;
        for(int f=0;f<(int)facets.size();f++)if(!isvis[f])nf.push_back(facets[f]);
        for(auto&kv:ecount)if(kv.second==1){
            int u=kv.first.first,v=kv.first.second;
            int a=u,b=v;
            if(orientInner(a,b,p)>0)swap(a,b);
            nf.push_back({a,b,p});
        }
        facets.swap(nf);
    }
    struct T{int x,y,z;};
    vector<T>out;
    for(auto&fc:facets){
        int v[3]={fc.a,fc.b,fc.c};
        sort(v,v+3);
        out.push_back({v[0],v[1],v[2]});
    }
    sort(out.begin(),out.end(),[](const T&a,const T&b){
        if(a.x!=b.x)return a.x<b.x;
        if(a.y!=b.y)return a.y<b.y;
        return a.z<b.z;
    });
    cout<<out.size()<<"\n";
    for(auto&tt:out)cout<<tt.x<<" "<<tt.y<<" "<<tt.z<<"\n";
    return 0;
}
