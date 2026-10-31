#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Priority search tree (de Berg 10.2): heap on y, BST on x, O(n)
// space. Nodes store their subtree's max-y point; 3-sided queries
// prune by x-range overlap and child-root y. Integer coordinates.
struct Pt{long long x,y;};
struct Node{Pt p;long long xmin,xmax;int left,right;};
vector<Pt>pts;
vector<int>xs;
vector<Node>tree;
int build(vector<int>&ids){
    int best=0;
    for(int i=1;i<(int)ids.size();i++)if(pts[ids[i]].y>pts[ids[best]].y)best=i;
    int pid=ids[best];
    vector<int>rest;
    for(int i=0;i<(int)ids.size();i++)if(i!=best)rest.push_back(ids[i]);
    // rest is x-sorted (ids were); split at pid's x-position: left = before pid, right = after
    vector<int> L,R;
    bool seen=false;
    for(int i=0;i<(int)ids.size();i++){
        if(i==best){seen=true;continue;}
        if(!seen)L.push_back(ids[i]);else R.push_back(ids[i]);
    }
    (void)rest;
    int id=(int)tree.size();
    tree.push_back(Node());
    int l=-1,r=-1;
    if(!L.empty())l=build(L);
    if(!R.empty())r=build(R);
    long long xmin=pts[pid].x,xmax=pts[pid].x;
    if(l>=0){xmin=min(xmin,tree[l].xmin);xmax=max(xmax,tree[l].xmax);}
    if(r>=0){xmin=min(xmin,tree[r].xmin);xmax=max(xmax,tree[r].xmax);}
    tree[id]={pts[pid],xmin,xmax,l,r};
    return id;
}
void query(int v,long long x1,long long x2,long long y0,vector<Pt>&out){
    if(v<0)return;
    Node&nd=tree[v];
    if(nd.p.y>=y0&&x1<=nd.p.x&&nd.p.x<=x2)out.push_back(nd.p);
    if(nd.left>=0){
        Node&c=tree[nd.left];
        if(c.xmax>=x1&&c.xmin<=x2&&c.p.y>=y0)query(nd.left,x1,x2,y0,out);
    }
    if(nd.right>=0){
        Node&c=tree[nd.right];
        if(c.xmax>=x1&&c.xmin<=x2&&c.p.y>=y0)query(nd.right,x1,x2,y0,out);
    }
}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    pts.resize(n);
    for(int i=0;i<n;i++)cin>>pts[i].x>>pts[i].y;
    xs.resize(n);
    for(int i=0;i<n;i++)xs[i]=i;
    sort(xs.begin(),xs.end(),[](int a,int b){return pts[a].x!=pts[b].x?pts[a].x<pts[b].x:pts[a].y<pts[b].y;});
    vector<int>ids=xs;
    tree.reserve(n);
    int root=build(ids);
    int q;cin>>q;
    for(int i=0;i<q;i++){
        long long x1,x2,y0;cin>>x1>>x2>>y0;
        vector<Pt>found;
        query(root,x1,x2,y0,found);
        sort(found.begin(),found.end(),[](const Pt&a,const Pt&b){return a.x!=b.x?a.x<b.x:a.y<b.y;});
        cout<<found.size()<<"\n";
        if(!found.empty()){
            for(size_t k=0;k<found.size();k++){if(k)cout<<" ";cout<<found[k].x<<","<<found[k].y;}
            cout<<"\n";
        }
    }
    return 0;
}
