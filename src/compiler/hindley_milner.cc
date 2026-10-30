
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
// Types: Var(id), Con(name), Arrow(l,r)
struct Ty{ int kind; int id; string name; Ty *l,*r; }; // kind 0=var 1=con 2=arrow
Ty* TVar(int id){ Ty*t=new Ty(); t->kind=0; t->id=id; return t; }
Ty* TCon(string n){ Ty*t=new Ty(); t->kind=1; t->name=n; return t; }
Ty* TArr(Ty*a,Ty*b){ Ty*t=new Ty(); t->kind=2; t->l=a; t->r=b; return t; }
typedef map<int,Ty*> Subst;
Ty* applyS(Subst& s, Ty* t){
    if(t->kind==0){ auto it=s.find(t->id); if(it==s.end())return t; return applyS(s,it->second); }
    if(t->kind==1)return t;
    return TArr(applyS(s,t->l),applyS(s,t->r));
}
void ftv(Ty* t, set<int>& o){
    if(t->kind==0){o.insert(t->id);return;}
    if(t->kind==2){ftv(t->l,o);ftv(t->r,o);}
}
bool occurs(int v, Ty* t){ set<int> s; ftv(t,s); return s.count(v); }
Subst compS(Subst& s1, Subst& s2){
    Subst r;
    for(auto &kv:s2) r[kv.first]=applyS(s1,kv.second);
    for(auto &kv:s1) if(!r.count(kv.first)) r[kv.first]=kv.second;
    return r;
}
bool unify(Ty* a, Ty* b, Subst& s, Subst& out){
    a=applyS(s,a); b=applyS(s,b);
    if(a->kind==0){
        if(b->kind==0&&a->id==b->id){out=s;return true;}
        if(occurs(a->id,b))return false;
        out=s; out[a->id]=b; return true;
    }
    if(b->kind==0){
        if(occurs(b->id,a))return false;
        out=s; out[b->id]=a; return true;
    }
    if(a->kind==1&&b->kind==1){ if(a->name!=b->name)return false; out=s; return true; }
    if(a->kind==2&&b->kind==2){
        Subst s1;
        if(!unify(a->l,b->l,s,s1))return false;
        return unify(a->r,b->r,s1,out);
    }
    return false;
}
// Exprs
struct Ex{ int kind; string atom; string var; Ex *a,*b,*c; }; // 0=atom 1=lam(var,body) 2=app 3=let(var,val,body) 4=if 5=binop(atom,e1,e2)
Ex* EAtom(string s){ Ex*e=new Ex(); e->kind=0; e->atom=s; return e; }
Ex* ELam(string v,Ex* b){ Ex*e=new Ex(); e->kind=1; e->var=v; e->a=b; return e; }
Ex* EApp(Ex*f,Ex*x){ Ex*e=new Ex(); e->kind=2; e->a=f; e->b=x; return e; }
Ex* ELet(string v,Ex*val,Ex*bo){ Ex*e=new Ex(); e->kind=3; e->var=v; e->a=val; e->b=bo; return e; }
Ex* EIf(Ex*c,Ex*t,Ex*e2){ Ex*e=new Ex(); e->kind=4; e->a=c; e->b=t; e->c=e2; return e; }
Ex* EBin(string op,Ex*x,Ex*y){ Ex*e=new Ex(); e->kind=5; e->atom=op; e->a=x; e->b=y; return e; }
struct Parser{ string s; size_t p; bool bad;
    void sp(){ while(p<s.size()&&isspace(s[p]))p++; }
    Ex* expr(){
        sp();
        if(p>=s.size()){bad=true;return nullptr;}
        if(s[p]=='('){
            p++; sp();
            string kw=atom();
            if(kw=="lam"){ sp(); string v=atom(); Ex* b=expr(); sp(); if(p>=s.size()||s[p]!=')'){bad=true;return nullptr;} p++; return ELam(v,b); }
            if(kw=="app"){ Ex* f=expr(); Ex* x=expr(); sp(); if(p>=s.size()||s[p]!=')'){bad=true;return nullptr;} p++; return EApp(f,x); }
            if(kw=="let"){ sp(); string v=atom(); Ex* val=expr(); Ex* bo=expr(); sp(); if(p>=s.size()||s[p]!=')'){bad=true;return nullptr;} p++; return ELet(v,val,bo); }
            if(kw=="if"){ Ex* c=expr(); Ex* t=expr(); Ex* e=expr(); sp(); if(p>=s.size()||s[p]!=')'){bad=true;return nullptr;} p++; return EIf(c,t,e); }
            if(kw=="+"||kw=="=="){ Ex* x=expr(); Ex* y=expr(); sp(); if(p>=s.size()||s[p]!=')'){bad=true;return nullptr;} p++; return EBin(kw,x,y); }
            bad=true; return nullptr;
        }
        string a=atom();
        if(a.empty()){bad=true;return nullptr;}
        return EAtom(a);
    }
    string atom(){
        sp();
        size_t q=p;
        while(q<s.size()&&!isspace(s[q])&&s[q]!='('&&s[q]!=')')q++;
        string r=s.substr(p,q-p); p=q; return r;
    }
};
struct Scheme{ vector<int> qs; Ty* t; };
typedef map<string,Scheme> Env;
int freshc;
Ty* fresh(){ return TVar(freshc++); }
void ftvEnv(Env& e, set<int>& o){
    for(auto &kv:e){ set<int> s; ftv(kv.second.t,s);
        for(int v:s){ bool q=false; for(int w:kv.second.qs)if(w==v)q=true; if(!q)o.insert(v); } }
}
Ty* inst(Scheme& sc){
    Subst s;
    for(int v:sc.qs) s[v]=fresh();
    return applyS(s,sc.t);
}
Scheme gen(Env& e, Ty* t){
    set<int> a,b; ftv(t,a); ftvEnv(e,b);
    Scheme sc; sc.t=t;
    for(int v:a)if(!b.count(v))sc.qs.push_back(v);
    return sc;
}
Env applyEnv(Subst& s, Env& e){
    Env r;
    for(auto &kv:e){ Scheme sc; sc.qs=kv.second.qs; sc.t=applyS(s,kv.second.t); r[kv.first]=sc; }
    return r;
}
bool infer(Env& env, Ex* e, Subst& s, Ty*& t);
bool infer(Env& env, Ex* e, Subst& s, Ty*& t){
    if(e->kind==0){
        string a=e->atom;
        bool isnum=!a.empty();
        for(char c:a)if(c<'0'||c>'9')isnum=false;
        if(isnum){ s.clear(); t=TCon("int"); return true; }
        if(a=="T"||a=="F"){ s.clear(); t=TCon("bool"); return true; }
        auto it=env.find(a);
        if(it==env.end())return false;
        s.clear(); t=inst(it->second); return true;
    }
    if(e->kind==1){
        Ty* b=fresh();
        Env e2=env; Scheme sc; sc.t=b; e2[e->var]=sc;
        Subst s1; Ty* t1;
        if(!infer(e2,e->a,s1,t1))return false;
        s=s1; t=TArr(applyS(s1,b),t1); return true;
    }
    if(e->kind==2){
        Subst s1,s2; Ty *t1,*t2;
        if(!infer(env,e->a,s1,t1))return false;
        Env e2=applyEnv(s1,env);
        if(!infer(e2,e->b,s2,t2))return false;
        Ty* b=fresh();
        Subst s3;
        Ty* u1=applyS(s2,t1);
        Ty* u2=TArr(t2,b);
        Subst emp1; if(!unify(u1,u2,emp1,s3))return false;
        Subst t12=compS(s2,s1);
        s=compS(s3,t12); t=applyS(s3,b); return true;
    }
    if(e->kind==3){
        Subst s1,s2; Ty *t1,*t2;
        if(!infer(env,e->a,s1,t1))return false;
        Env e2=applyEnv(s1,env);
        Scheme sc=gen(e2,t1);
        e2[e->var]=sc;
        if(!infer(e2,e->b,s2,t2))return false;
        s=compS(s2,s1); t=t2; return true;
    }
    if(e->kind==4){
        Subst s1,s2,s3; Ty *tc,*tt,*te;
        if(!infer(env,e->a,s1,tc))return false;
        Subst sa;
        if(!unify(tc,TCon("bool"),s1,sa))return false;
        Env e2=applyEnv(sa,env);
        if(!infer(e2,e->b,s2,tt))return false;
        Env e3=applyEnv(s2,e2);
        if(!infer(e3,e->c,s3,te))return false;
        Subst sb;
        Ty* u1=applyS(s3,tt);
        Subst emp2; if(!unify(u1,te,emp2,sb))return false;
        Subst t1=compS(s3,s2), t2=compS(t1,sa);
        s=compS(sb,t2); t=applyS(sb,te); return true;
    }
    if(e->kind==5){
        Subst s1,s2; Ty *t1,*t2;
        if(!infer(env,e->a,s1,t1))return false;
        Subst sa;
        if(!unify(t1,TCon("int"),s1,sa))return false;
        Env e2=applyEnv(sa,env);
        if(!infer(e2,e->b,s2,t2))return false;
        Subst sb;
        if(!unify(t2,TCon("int"),s2,sb))return false;
        Subst c1=compS(sb,s2), c2=compS(c1,sa);
        s=compS(c2,s1); t=(e->atom=="+"?TCon("int"):TCon("bool")); return true;
    }
    return false;
}
void collect(Ty* t, vector<int>& o){
    if(t->kind==0){ for(int v:o)if(v==t->id)return; o.push_back(t->id); return; }
    if(t->kind==2){collect(t->l,o);collect(t->r,o);}
}
string showT(Ty* t, map<int,string>& nm){
    if(t->kind==0)return nm[t->id];
    if(t->kind==1)return t->name;
    return "("+showT(t->l,nm)+" -> "+showT(t->r,nm)+")";
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; if(!(cin>>T)) return 0;
    string dummy; getline(cin,dummy);
    while(T--){
        string line;
        do{ if(!getline(cin,line))line=""; }while(line.size()==0&&!cin.eof());
        Parser ps; ps.s=line; ps.p=0; ps.bad=false;
        Ex* e=ps.expr(); ps.sp();
        if(ps.bad||ps.p!=line.size()){ cout<<"HM TYPE-ERROR\n"; continue; }
        freshc=0;
        Env env; Subst s; Ty* t;
        if(!infer(env,e,s,t)){ cout<<"HM TYPE-ERROR\n"; continue; }
        Ty* f=applyS(s,t);
        vector<int> vs; collect(f,vs);
        map<int,string> nm;
        for(size_t i=0;i<vs.size();i++)nm[vs[i]]=string(1,'a'+i);
        cout<<"HM "<<showT(f,nm)<<"\n";
    }
    return 0;
}
