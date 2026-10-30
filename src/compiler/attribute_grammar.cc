
#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Node{ Node* l; int bit; };
long long synth(Node* n){
    if(!n->l) return n->bit;
    return synth(n->l)*2+n->bit;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    while(T--){
        string sg,bs;cin>>sg>>bs;
        Node* root=nullptr;
        vector<Node> pool(bs.size());
        for(size_t i=0;i<bs.size();i++){
            pool[i].l=root; pool[i].bit=(bs[i]=='1'?1:0);
            root=&pool[i];
        }
        long long v=synth(root);
        if(sg=="-")v=-v;
        cout<<"ATTR "<<v<<"\n";
    }
    return 0;
}
