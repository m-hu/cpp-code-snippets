#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;
// Trapezoidal map + point-location DAG (de Berg 6.1-6.2): randomized
// incremental construction (fixed-seed shuffle) with history DAG.
// Single-segment case: each trapezoid's top/bottom segment ids
// (input order, -1 = bounding box) answer point location.
struct Pt{long long x,y;};
struct Seg{Pt a,b;}; // a.x <= b.x
long long cross(const Pt&a,const Pt&b,const Pt&c){return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int s;if(!(cin>>s))return 0;
    vector<Seg>segs(s);
    for(int i=0;i<s;i++){
        long long x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
        if(x1>x2){swap(x1,x2);swap(y1,y2);}
        segs[i]={{x1,y1},{x2,y2}};
    }
    // Fixed-seed LCG shuffle (deterministic "randomized" order).
    vector<int>ord(s);
    for(int i=0;i<s;i++)ord[i]=i;
    uint64_t st=192;
    auto rnd=[&]()->uint64_t{st=st*6364136223846793005ULL+1442695040888963407ULL;return st>>33;};
    for(int i=s-1;i>0;i--){int j=(int)(rnd()%(uint64_t)(i+1));swap(ord[i],ord[j]);}
    struct Trap{int top,bot;Pt lp,rp;};
    struct Node{
        int kind; // 0=trap,1=xnode,2=ynode
        int trap; // trap idx if kind 0
        Pt p;     // xnode point
        int seg;  // ynode seg id
        int left,right; // children (xnode: left/right; ynode: above=left,below=right)
    };
    vector<Trap>traps;
    vector<Node>nodes;
    long long X0=4e12,X1=-4e12;
    for(auto&sg:segs){X0=min(X0,min(sg.a.x,sg.b.x)-1);X1=max(X1,max(sg.a.x,sg.b.x)+1);}
    traps.push_back({-1,-1,{X0,0},{X1,0}});
    nodes.push_back({0,0,{0,0},-1,-1,-1});
    auto above=[&](int si,Pt p)->bool{
        // is p strictly above segment si (evaluated at p.x)?
        Pt a=segs[si].a,b=segs[si].b;
        if(a.x==b.x) return false; // vertical: queries avoid; treat as below
        return cross(a,b,p)>0;
    };
    for(int oi=0;oi<s;oi++){
        int si=ord[oi];
        Pt p=segs[si].a,q=segs[si].b;
        // Collect current leaf traps (kind 0 = never split) whose
        // x-range strictly overlaps [p.x,q.x] and that straddle si.
        vector<int>leaves;
        for(int ni=0;ni<(int)nodes.size();ni++)if(nodes[ni].kind==0)leaves.push_back(ni);
        // Find traps crossed by si: those with x-overlap and si passing through interior.
        vector<int>hits;
        for(int ni:leaves){
            Trap T=traps[nodes[ni].trap];
            if(T.rp.x<=p.x||T.lp.x>=q.x)continue;
            // vertical line sample: check si passes between top and bot within overlap
            // sample x mid of overlap
            double xm=(max<double>((double)T.lp.x,(double)p.x)+min<double>((double)T.rp.x,(double)q.x))/2.0L;
            // y of si at xm
            double t=(xm-(double)p.x)/(double)(q.x-p.x);
            double ys=(double)p.y+t*(double)(q.y-p.y);
            // top/bot y at xm
            double yt=4e18,yb=-4e18;
            if(T.top>=0){Seg sg=segs[T.top];double tt=(xm-(double)sg.a.x)/(double)(sg.b.x-sg.a.x);yt=(double)sg.a.y+tt*(double)(sg.b.y-sg.a.y);}
            if(T.bot>=0){Seg sg=segs[T.bot];double tt=(xm-(double)sg.a.x)/(double)(sg.b.x-sg.a.x);yb=(double)sg.a.y+tt*(double)(sg.b.y-sg.a.y);}
            if(yb<ys&&ys<yt)hits.push_back(ni);
        }
        sort(hits.begin(),hits.end(),[&](int a,int b){return traps[nodes[a].trap].lp.x<traps[nodes[b].trap].lp.x;});
        // Split each hit trap; merge upper/lower neighbors sharing top/bottom (cking: merge into at most ... keep simple: split all, no merge of uppers/lowers except identical (top,bot,lp,rp) dedup via shared nodes? For query correctness merging is unneeded.)
        // Standard single-trap case + multi-trap case with left/right end traps.
        int nh=(int)hits.size();
        for(int hi=0;hi<nh;hi++){
            int ni=hits[hi];
            Trap T=traps[nodes[ni].trap];
            bool first=(hi==0),last=(hi==nh-1);
            int top=T.top,bot=T.bot;
            // upper piece: top/si from max(lp,p) to min(rp,q); lower: si/bot same span
            Pt ulp=T.lp.x<p.x?p:T.lp, urp=T.rp.x>q.x?q:T.rp;
            int upT=(int)traps.size();traps.push_back({top,si,ulp,urp});
            int loT=(int)traps.size();traps.push_back({si,bot,ulp,urp});
            int upN=(int)nodes.size();nodes.push_back({0,upT,{0,0},-1,-1,-1});
            int loN=(int)nodes.size();nodes.push_back({0,loT,{0,0},-1,-1,-1});
            int yN=(int)nodes.size();nodes.push_back({2,-1,{0,0},si,upN,loN});
            int rep=yN;
            if(first&&T.lp.x<p.x){
                int lT=(int)traps.size();traps.push_back({top,bot,T.lp,p});
                int lN=(int)nodes.size();nodes.push_back({0,lT,{0,0},-1,-1,-1});
                int xN=(int)nodes.size();nodes.push_back({1,-1,p,-1,lN,rep});
                rep=xN;
            }
            if(last&&T.rp.x>q.x){
                int rT=(int)traps.size();traps.push_back({top,bot,q,T.rp});
                int rN=(int)nodes.size();nodes.push_back({0,rT,{0,0},-1,-1,-1});
                int xN=(int)nodes.size();nodes.push_back({1,-1,q,-1,rep,rN});
                rep=xN;
            }
            // convert ni from trap node to pointer: mark by replacing with redirect node kind 3
            nodes[ni].kind=3;nodes[ni].left=rep;
        }
    }
    auto query=[&](Pt qq){
        int ni=0;
        while(true){
            Node&nd=nodes[ni];
            if(nd.kind==0)return nodes[ni].trap;
            if(nd.kind==3){ni=nd.left;continue;}
            if(nd.kind==1){ni=(qq.x<nd.p.x)?nd.left:nd.right;continue;}
            // ynode
            ni=above(nd.seg,qq)?nd.left:nd.right;
        }
    };
    int qq;cin>>qq;
    for(int i=0;i<qq;i++){
        Pt g;cin>>g.x>>g.y;
        Trap T=traps[query(g)];
        cout<<T.top<<" "<<T.bot<<"\n";
    }
    return 0;
}
