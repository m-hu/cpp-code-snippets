
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int F,D;
vector<vector<int>> X; vector<int> Y;
double entropy(const vector<int>& idx){
    if(idx.empty())return 0;
    int c=0;
    for(int i:idx)if(Y[i]==1)c++;
    double p=(double)c/idx.size();
    if(p==0||p==1)return 0;
    return -(p*log(p)+(1-p)*log(1-p));
}
struct Node{ bool leaf; int label, feat; Node *l,*r; int depth; };
static vector<Node*> _pool;
Node* build(const vector<int>& idx, int used, int depth, int parent_maj){
    int c0=0,c1=0;
    for(int i:idx)(Y[i]==1?c1:c0)++;
    Node* nd=new Node(); _pool.push_back(nd); nd->depth=depth;
    if(idx.empty()){nd->leaf=true;nd->label=parent_maj;nd->l=nd->r=nullptr;return nd;}
    if(c0==0||c1==0||depth>=D||used==(1<<F)){
        nd->leaf=true;nd->label=(c1>=c0?1:0);nd->l=nd->r=nullptr;return nd;
    }
    double base=entropy(idx);
    int bf=-1; double bg=-1;
    for(int f=0;f<F;f++){
        if(used>>f&1)continue;
        vector<int> L,R;
        for(int i:idx)((X[i][f]==0?L:R).push_back(i));
        double g=base-(double)L.size()/idx.size()*entropy(L)-(double)R.size()/idx.size()*entropy(R);
        if(g>bg+1e-12){bg=g;bf=f;}
    }
    int maj=(c1>=c0?1:0);
    vector<int> L,R;
    for(int i:idx)((X[i][bf]==0?L:R).push_back(i));
    nd->leaf=false;nd->feat=bf;
    nd->l=build(L,used|(1<<bf),depth+1,maj);
    nd->r=build(R,used|(1<<bf),depth+1,maj);
    return nd;
}
int predict(Node* nd,const vector<int>& x){
    while(!nd->leaf)nd=(x[nd->feat]==0?nd->l:nd->r);
    return nd->label;
}
int maxdepth(Node* nd){
    if(nd->leaf)return nd->depth;
    return max(maxdepth(nd->l),maxdepth(nd->r));
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        int N;cin>>N>>F>>D;
        X.assign(N,vector<int>(F));Y.assign(N,0);
        for(int i=0;i<N;i++){for(int f=0;f<F;f++)cin>>X[i][f];cin>>Y[i];}
        vector<int> all(N);for(int i=0;i<N;i++)all[i]=i;
        Node* root=build(all,0,0,1);
        cout<<"DT "<<maxdepth(root)<<"\n";
        for(int i=0;i<N;i++){if(i)cout<<' ';cout<<predict(root,X[i]);}
        cout<<"\n";
    }
    for(Node* p:_pool)delete p;
    return 0;
}
