#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    string s1,s2; if(!(cin>>s1>>s2)) return 0;
    int n=s1.size(),m=s2.size();
    const int NEG=-1e9;
    const int MATCH=2,MISMATCH=-1,GAP_OPEN=-2,GAP_EXTEND=-1;
    vector<vector<int>> M(n+1,vector<int>(m+1,NEG)), Ix(n+1,vector<int>(m+1,NEG)), Iy(n+1,vector<int>(m+1,NEG));
    M[0][0]=0;
    for(int i=1;i<=n;i++) Ix[i][0]=GAP_OPEN+(i-1)*GAP_EXTEND;
    for(int j=1;j<=m;j++) Iy[0][j]=GAP_OPEN+(j-1)*GAP_EXTEND;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        int sc=(s1[i-1]==s2[j-1]?MATCH:MISMATCH);
        M[i][j]=max({M[i-1][j-1],Ix[i-1][j-1],Iy[i-1][j-1]})+sc;
        Ix[i][j]=max(M[i-1][j]+GAP_OPEN, Ix[i-1][j]+GAP_EXTEND);
        Iy[i][j]=max(M[i][j-1]+GAP_OPEN, Iy[i][j-1]+GAP_EXTEND);
    }
    cout<<max({M[n][m],Ix[n][m],Iy[n][m]})<<"\n";
    return 0;
}
