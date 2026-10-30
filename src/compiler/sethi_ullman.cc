#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string> toks; size_t p;
struct Node{bool leaf; string label; Node *l,*r; int su;};
Node* parse(){
    if(toks[p]=="("){p++; string op=toks[p++]; Node* L=parse(); Node* R=parse(); p++;
        Node* n=new Node(); n->leaf=false; n->label=op; n->l=L; n->r=R;
        n->su = (L->su==R->su)? L->su+1 : max(L->su,R->su);
        return n;}
    Node* n=new Node(); n->leaf=true; n->label=toks[p++]; n->l=n->r=nullptr; n->su=1;
    return n;
}
void order(Node* n, vector<string>& out){
    if(n->leaf){out.push_back(n->label); return;}
    if(n->r->su > n->l->su){order(n->r,out); order(n->l,out);}
    else{order(n->l,out); order(n->r,out);}
    out.push_back(n->label);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    string line; getline(cin,line);
    for(int tc=0;tc<T;tc++){
        getline(cin,line);
        toks.clear(); p=0;
        string cur;
        for(char c:line){
            if(c==' '||c=='\t'){if(!cur.empty()){toks.push_back(cur);cur="";}}
            else if(c=='('||c==')'){if(!cur.empty()){toks.push_back(cur);cur="";} toks.push_back(string(1,c));}
            else cur+=c;
        }
        if(!cur.empty()) toks.push_back(cur);
        Node* r=parse();
        cout<<"SU "<<r->su<<"\nORDER";
        vector<string> o; order(r,o);
        for(size_t i=0;i<o.size();i++) cout<<" "<<o[i];
        cout<<"\n";
    }
    return 0;
}
