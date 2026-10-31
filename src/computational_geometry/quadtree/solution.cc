#include <iostream>
#include <vector>
#include <functional>
#include <utility>
using namespace std;
// Point-region quadtree over [0,S)x[0,S): split while a node holds
// more than cap points (or size 1); children SW,SE,NW,NE. Preorder
// dump, then pruned rectangle counting queries.
struct Node{bool leaf;int x,y,s;int c[4];vector<int>ids;};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,S,cap;if(!(cin>>n>>S>>cap))return 0;
    vector<int>px(n),py(n);
    for(int i=0;i<n;i++)cin>>px[i]>>py[i];
    vector<Node>nodes;
    function<int(vector<int>,int,int,int)>rec=[&](vector<int>ids,int x,int y,int s)->int{
        if((int)ids.size()<=cap||s==1){
            Node nd;nd.leaf=true;nd.x=x;nd.y=y;nd.s=s;nd.ids=std::move(ids);
            nodes.push_back(std::move(nd));return (int)nodes.size()-1;
        }
        int h=s/2;
        vector<int>q[4];
        for(int i:ids){
            int k=(px[i]<x+h?0:1)+(py[i]<y+h?0:2);
            q[k].push_back(i);
        }
        Node nd;nd.leaf=false;nd.x=x;nd.y=y;nd.s=s;
        int qx[4]={x,x+h,x,x+h},qy[4]={y,y,y+h,y+h},qs[4]={h,s-h,h,s-h};
        int idx=(int)nodes.size();nodes.push_back(std::move(nd));
        for(int k=0;k<4;k++)nodes[idx].c[k]=q[k].empty()?-1:rec(q[k],qx[k],qy[k],qs[k]);
        return idx;
    };
    vector<int>all(n);for(int i=0;i<n;i++)all[i]=i;
    rec(all,0,0,S);
    cout<<nodes.size()<<"\n";
    for(auto&nd:nodes){
        if(!nd.leaf)cout<<"I "<<nd.x<<" "<<nd.y<<" "<<nd.s<<" "<<nd.c[0]<<" "<<nd.c[1]<<" "<<nd.c[2]<<" "<<nd.c[3]<<"\n";
        else{cout<<"L "<<nd.x<<" "<<nd.y<<" "<<nd.s<<" "<<nd.ids.size();for(int i:nd.ids)cout<<" "<<i;cout<<"\n";}
    }
    function<int(int,int,int,int,int)>count=[&](int ni,int x1,int y1,int x2,int y2)->int{
        const Node&nd=nodes[ni];
        if(nd.leaf){int c=0;for(int i:nd.ids)if(px[i]>=x1&&px[i]<=x2&&py[i]>=y1&&py[i]<=y2)c++;return c;}
        int h=nd.s/2;
        int rx[4]={nd.x,nd.x+h,nd.x,nd.x+h},ry[4]={nd.y,nd.y,nd.y+h,nd.y+h},rs[4]={h,nd.s-h,h,nd.s-h};
        int tot=0;
        for(int k=0;k<4;k++){
            if(nd.c[k]==-1)continue;
            if(rx[k]>x2||rx[k]+rs[k]-1<x1||ry[k]>y2||ry[k]+rs[k]-1<y1)continue;
            tot+=count(nd.c[k],x1,y1,x2,y2);
        }
        return tot;
    };
    int qq;cin>>qq;
    for(int i=0;i<qq;i++){int x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;cout<<count(0,x1,y1,x2,y2)<<"\n";}
    return 0;
}
