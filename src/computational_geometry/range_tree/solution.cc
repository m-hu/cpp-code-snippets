#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 2D orthogonal range tree with fractional cascading (de Berg 5.3-5.6).
// Primary x-tree; each node stores subtree points by y plus cascade
// pointers into children's y-arrays. One binary search at the split
// node, O(1) range propagation per level. Integer coordinates.
struct Pt{long long x,y;};
struct Node{
    int l,r,mid,left,right;
    vector<int>yvec;
    vector<int>fcl,fcr;
};
vector<Pt>pts;
vector<int>xs;
vector<Node>tree;
int build(int l,int r){
    int id=(int)tree.size();
    tree.push_back(Node());
    tree[id].l=l;tree[id].r=r;
    vector<int>yv;
    for(int i=l;i<r;i++)yv.push_back(xs[i]);
    sort(yv.begin(),yv.end(),[](int a,int b){return pts[a].y!=pts[b].y?pts[a].y<pts[b].y:pts[a].x<pts[b].x;});
    tree[id].yvec=yv;
    if(r-l==1){tree[id].mid=l;tree[id].left=tree[id].right=-1;return id;}
    int mid=(l+r)/2;
    tree[id].mid=mid;
    int L=build(l,mid),R=build(mid,r);
    tree[id].left=L;tree[id].right=R;
    int ys=(int)yv.size();
    tree[id].fcl.assign(ys+1,0);tree[id].fcr.assign(ys+1,0);
    vector<int>&ly=tree[L].yvec,&ry=tree[R].yvec;
    for(int i=0;i<=ys;i++){
        long long yb=(i<ys)?pts[yv[i]].y:(long long)4e18;
        int lo=0,hi=(int)ly.size();
        while(lo<hi){int mm=(lo+hi)/2;if(pts[ly[mm]].y<yb)lo=mm+1;else hi=mm;}
        tree[id].fcl[i]=lo;
        lo=0;hi=(int)ry.size();
        while(lo<hi){int mm=(lo+hi)/2;if(pts[ry[mm]].y<yb)lo=mm+1;else hi=mm;}
        tree[id].fcr[i]=hi;
    }
    return id;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    pts.resize(n);
    for(int i=0;i<n;i++)cin>>pts[i].x>>pts[i].y;
    xs.resize(n);
    for(int i=0;i<n;i++)xs[i]=i;
    sort(xs.begin(),xs.end(),[](int a,int b){return pts[a].x!=pts[b].x?pts[a].x<pts[b].x:pts[a].y<pts[b].y;});
    tree.reserve(2*n);
    int root=build(0,n);
    auto yval=[](int pid){return pts[pid].y;};
    int q;cin>>q;
    for(int qi=0;qi<q;qi++){
        long long x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
        vector<int>found;
        int v=root;
        while(tree[v].left!=-1){
            long long key=pts[xs[tree[v].mid]].x;
            if(x2<key)v=tree[v].left;
            else if(x1>key)v=tree[v].right;
            else break;
        }
        if(tree[v].left==-1){
            int pid=tree[v].yvec[0];
            if(x1<=pts[pid].x&&pts[pid].x<=x2&&y1<=pts[pid].y&&pts[pid].y<=y2)found.push_back(pid);
        }else{
            vector<int>&syv=tree[v].yvec;
            int lo=0,hi=(int)syv.size();
            while(lo<hi){int mm=(lo+hi)/2;if(yval(syv[mm])<y1)lo=mm+1;else hi=mm;}
            int lo0=lo;lo=0;hi=(int)syv.size();
            long long y2p=(y2==(long long)4e18-1)?(long long)4e18:y2+1;
            while(lo<hi){int mm=(lo+hi)/2;if(yval(syv[mm])<y2p)lo=mm+1;else hi=mm;}
            int hi0=lo;
            int lv=tree[v].left,rv=tree[v].right;
            int llo=tree[v].fcl[lo0],lhi=tree[v].fcl[hi0];
            int rlo=tree[v].fcr[lo0],rhi=tree[v].fcr[hi0];
            // left walk
            int u=lv,a=llo,b=lhi;
            while(true){
                if(tree[u].left==-1){
                    if(b>a){int pid=tree[u].yvec[0];if(x1<=pts[pid].x)found.push_back(pid);}
                    break;
                }
                long long key=pts[xs[tree[u].mid]].x;
                if(x1<=key){
                    int c=tree[u].right;
                    for(int i=tree[u].fcr[a];i<tree[u].fcr[b];i++)found.push_back(tree[c].yvec[i]);
                    int nl=tree[u].left;
                    int na=tree[u].fcl[a],nb=tree[u].fcl[b];
                    u=nl;a=na;b=nb;
                }else{
                    int nr=tree[u].right;
                    int na=tree[u].fcr[a],nb=tree[u].fcr[b];
                    u=nr;a=na;b=nb;
                }
            }
            // right walk
            u=rv;a=rlo;b=rhi;
            while(true){
                if(tree[u].left==-1){
                    if(b>a){int pid=tree[u].yvec[0];if(pts[pid].x<=x2)found.push_back(pid);}
                    break;
                }
                long long key=pts[xs[tree[u].mid]].x;
                if(key<=x2){
                    int c=tree[u].left;
                    for(int i=tree[u].fcl[a];i<tree[u].fcl[b];i++)found.push_back(tree[c].yvec[i]);
                    int nr2=tree[u].right;
                    int na=tree[u].fcr[a],nb=tree[u].fcr[b];
                    u=nr2;a=na;b=nb;
                }else{
                    int nl=tree[u].left;
                    int na=tree[u].fcl[a],nb=tree[u].fcl[b];
                    u=nl;a=na;b=nb;
                }
            }
        }
        sort(found.begin(),found.end(),[](int a,int b){return pts[a].x!=pts[b].x?pts[a].x<pts[b].x:pts[a].y<pts[b].y;});
        cout<<found.size()<<"\n";
        if(!found.empty()){
            for(size_t i=0;i<found.size();i++){if(i)cout<<" ";cout<<pts[found[i]].x<<","<<pts[found[i]].y;}
            cout<<"\n";
        }
    }
    return 0;
}
