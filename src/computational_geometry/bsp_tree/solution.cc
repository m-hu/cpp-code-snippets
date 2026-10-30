#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <string>
#include <utility>
using namespace std;
// BSP tree: autopartition, first segment as splitter; strictly one-sided
// segments recurse, straddling/touching ones stored at the node.
struct Seg{long long x1,y1,x2,y2;};
long long orient(const Seg&a,long long px,long long py){
    return (a.x2-a.x1)*(py-a.y1)-(a.y2-a.y1)*(px-a.x1);
}
struct Node{Seg sp;int sid;vector<int>at;int L=-1,R=-1;};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<Seg>segs(n);for(auto&s:segs)cin>>s.x1>>s.y1>>s.x2>>s.y2;
    vector<Node>nodes;
    function<int(vector<int>)>build=[&](vector<int>ids)->int{
        if(ids.empty())return -1;
        Node nd;nd.sid=ids[0];nd.sp=segs[ids[0]];nd.at.push_back(ids[0]);
        vector<int>left,right;
        for(size_t k=1;k<ids.size();k++){
            int i=ids[k];
            long long o1=orient(nd.sp,segs[i].x1,segs[i].y1);
            long long o2=orient(nd.sp,segs[i].x2,segs[i].y2);
            if(o1<0&&o2<0)left.push_back(i);
            else if(o1>0&&o2>0)right.push_back(i);
            else nd.at.push_back(i);
        }
        int idx=(int)nodes.size();nodes.push_back(std::move(nd));
        nodes[idx].L=build(left);nodes[idx].R=build(right);
        return idx;
    };
    vector<int>all(n);iota(all.begin(),all.end(),0);
    build(all);
    cout<<nodes.size()<<"\n";
    for(auto&nd:nodes){
        cout<<nd.sp.x1<<" "<<nd.sp.y1<<" "<<nd.sp.x2<<" "<<nd.sp.y2<<" "<<nd.L<<" "<<nd.R<<" "<<nd.at.size();
        for(int i:nd.at)cout<<" "<<i;
        cout<<"\n";
    }
    int q;cin>>q;
    for(int i=0;i<q;i++){
        long long x,y;cin>>x>>y;
        int node=0;string path;
        while(true){
            long long o=orient(nodes[node].sp,x,y);
            if(o<0){if(nodes[node].L==-1)break;if(!path.empty())path+=" ";path+="L";node=nodes[node].L;}
            else if(o>0){if(nodes[node].R==-1)break;if(!path.empty())path+=" ";path+="R";node=nodes[node].R;}
            else{if(!path.empty())path+=" ";path+="=";break;}
        }
        cout<<(path.empty()?"-":path)<<" "<<node<<"\n";
    }
    return 0;
}
