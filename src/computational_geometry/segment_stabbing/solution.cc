#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Segment tree stabbing queries (de Berg 10.3): elementary intervals
// from unique endpoints; segments stored at canonical nodes covering
// their span; point query collects sets along the root-leaf path.
struct ST{
    int n;
    vector<vector<int>>t;
    ST(int n=0){init(n);}
    void init(int n_){n=n_;t.assign(4*n,{});}
    void insert(int v,int l,int r,int ql,int qr,int id){
        if(ql>=r||qr<=l)return;
        if(ql<=l&&r<=qr){t[v].push_back(id);return;}
        int m=(l+r)/2;
        insert(2*v,l,m,ql,qr,id);insert(2*v+1,m,r,ql,qr,id);
    }
    void insert(int ql,int qr,int id){insert(1,0,n,ql,qr,id);}
    void query(int v,int l,int r,int i,vector<int>&out){
        for(int id:t[v])out.push_back(id);
        if(r-l==1)return;
        int m=(l+r)/2;
        if(i<m)query(2*v,l,m,i,out);else query(2*v+1,m,r,i,out);
    }
    void query(int i,vector<int>&out){query(1,0,n,i,out);}
};
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n;if(!(cin>>n))return 0;
    vector<long long>L(n),R(n);
    vector<long long>u;
    for(int i=0;i<n;i++){cin>>L[i]>>R[i];u.push_back(L[i]);u.push_back(R[i]);}
    sort(u.begin(),u.end());u.erase(unique(u.begin(),u.end()),u.end());
    int m=(int)u.size();
    ST st(2*m+1);
    for(int i=0;i<n;i++){
        int li=lower_bound(u.begin(),u.end(),L[i])-u.begin();
        int ri=lower_bound(u.begin(),u.end(),R[i])-u.begin();
        st.insert(2*li+1,2*ri+2,i);
    }
    int q;cin>>q;
    for(int i=0;i<q;i++){
        long long x;cin>>x;
        int ei;
        if(x<u[0])ei=0;
        else if(x>u[m-1])ei=2*m;
        else{
            int k=upper_bound(u.begin(),u.end(),x)-u.begin()-1;
            ei=(u[k]==x)?2*k+1:2*k+2;
        }
        vector<int>found;
        st.query(ei,found);
        sort(found.begin(),found.end());
        cout<<found.size()<<"\n";
        if(!found.empty()){
            for(size_t k=0;k<found.size();k++){if(k)cout<<" ";cout<<found[k];}
            cout<<"\n";
        }
    }
    return 0;
}
