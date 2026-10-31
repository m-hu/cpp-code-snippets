
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n)) return 0;
    string line;
    getline(cin,line);
    vector<map<string,string> > scopes(1);
    vector<int> chain(1,0);
    int nextid=1, declares=0, errors=0;
    for(int i=0;i<n;i++){
        getline(cin,line);
        stringstream ss(line);
        vector<string> t; string w;
        while(ss>>w) t.push_back(w);
        if(t.empty()){i--;continue;}
        if(t[0]=="ENTER"){
            scopes.push_back(map<string,string>());
            chain.push_back(nextid++);
            cout<<"ENTER "<<(scopes.size()-1)<<"\n";
        }else if(t[0]=="EXIT"){
            if(scopes.size()<=1){cout<<"EXIT UNDERFLOW\n";errors++;}
            else{scopes.pop_back();chain.pop_back();cout<<"EXIT "<<(scopes.size()-1)<<"\n";}
        }else if(t[0]=="DECLARE"&&t.size()>=3){
            if(scopes.back().count(t[1])){cout<<"DECLARE "<<t[1]<<" "<<t[2]<<" REDECLARED\n";errors++;}
            else{scopes.back()[t[1]]=t[2];cout<<"DECLARE "<<t[1]<<" "<<t[2]<<" OK\n";declares++;}
        }else if(t[0]=="LOOKUP"&&t.size()>=2){
            bool found=false;
            for(int d=(int)scopes.size()-1;d>=0;d--){
                auto it=scopes[d].find(t[1]);
                if(it!=scopes[d].end()){cout<<"LOOKUP "<<t[1]<<" "<<it->second<<" "<<d<<"\n";found=true;break;}
            }
            if(!found){cout<<"LOOKUP "<<t[1]<<" UNDECLARED\n";errors++;}
        }else if(t[0]=="ASSIGN"&&t.size()>=2){
            bool found=false;
            for(int d=(int)scopes.size()-1;d>=0;d--){
                if(scopes[d].count(t[1])){cout<<"ASSIGN "<<t[1]<<" OK "<<d<<"\n";found=true;break;}
            }
            if(!found){cout<<"ASSIGN "<<t[1]<<" UNDECLARED\n";errors++;}
        }else if(t[0]=="DISPLAY"){
            cout<<"DISPLAY";
            for(size_t d=0;d<chain.size();d++) cout<<" "<<d<<":"<<chain[d];
            cout<<"\n";
        }
    }
    cout<<"SYMTAB declares="<<declares<<" errors="<<errors<<"\n";
    return 0;
}
