#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
// Small parsimony (Gusfield 17.5): Fitch set DP + Sankoff cost DP
// (unit costs) on a rooted tree. Output: "F S" then Fitch root set.
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<vector<int>>ch(n);
    for(int e=0;e<n-1;e++){int p,c;cin>>p>>c;ch[p].push_back(c);}
    int L;cin>>L;
    vector<char>leaf(n,0);vector<char>alpha;
    for(int i=0;i<L;i++){int id;char st;cin>>id>>st;leaf[id]=st;alpha.push_back(st);}
    sort(alpha.begin(),alpha.end());alpha.erase(unique(alpha.begin(),alpha.end()),alpha.end());
    vector<int>order;vector<char>seen(n,0);
    vector<int>st;st.push_back(0);seen[0]=1;
    while(!st.empty()){int u=st.back();st.pop_back();order.push_back(u);for(int v:ch[u])if(!seen[v]){seen[v]=1;st.push_back(v);}}
    // Fitch (generalized: min-mismatch states; intersection/union on binary)
    vector<set<char>>fs(n);
    int fcost=0;
    for(int k=(int)order.size()-1;k>=0;k--){
        int u=order[k];
        if(ch[u].empty()){fs[u].insert(leaf[u]);continue;}
        int best=1e9;set<char>bs;
        for(char a:alpha){
            int mm=0;for(int v:ch[u])if(!fs[v].count(a))mm++;
            if(mm<best){best=mm;bs.clear();bs.insert(a);}else if(mm==best)bs.insert(a);
        }
        fs[u]=bs;fcost+=best;
    }
    // Sankoff
    const int INF=1000000000;
    int na=(int)alpha.size();
    map<char,int>ai;for(int i=0;i<na;i++)ai[alpha[i]]=i;
    vector<vector<int>>sc(n,vector<int>(na,INF));
    for(int k=(int)order.size()-1;k>=0;k--){
        int u=order[k];
        if(ch[u].empty()){sc[u][ai[leaf[u]]]=0;continue;}
        for(int a=0;a<na;a++){
            int tot=0;
            for(int v:ch[u]){
                int best=INF;
                for(int b=0;b<na;b++)best=min(best,sc[v][b]+(a==b?0:1));
                tot+=best;
            }
            sc[u][a]=tot;
        }
    }
    int scost=INF;for(int a=0;a<na;a++)scost=min(scost,sc[0][a]);
    cout<<fcost<<" "<<scost<<"\n";
    for(char x:fs[0])cout<<x;
    cout<<"\n";
    return 0;
}
