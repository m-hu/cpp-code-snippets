#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <deque>
#include <numeric>
#include <functional>
using namespace std;

int N;vector<vector<long long>>A,B,C;
void rec(int a0,int a1,int b0,int b1,int c0,int c1,int s){
if(s<=2){for(int i=0;i<s;i++)for(int k=0;k<s;k++)for(int j=0;j<s;j++)
C[c0+i][c1+j]+=A[a0+i][a1+k]*B[b0+k][b1+j];return;}
int h=s/2;
rec(a0,a1,b0,b1,c0,c1,h);rec(a0,a1+h,b0+h,b1,c0,c1,h);
rec(a0,a1,b0,b1+h,c0,c1+h,h);rec(a0,a1+h,b0+h,b1+h,c0,c1+h,h);
rec(a0+h,a1,b0,b1,c0+h,c1,h);rec(a0+h,a1+h,b0+h,b1,c0+h,c1,h);
rec(a0+h,a1,b0,b1+h,c0+h,c1+h,h);rec(a0+h,a1+h,b0+h,b1+h,c0+h,c1+h,h);}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);
int n; if(!(cin>>n)) return 0;
N=1;while(N<n)N*=2;
A.assign(N,vector<long long>(N,0));B=A;C=A;
for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>A[i][j];
for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin>>B[i][j];
rec(0,0,0,0,0,0,N);
for(int i=0;i<n;i++){for(int j=0;j<n;j++){if(j)cout<<" ";cout<<C[i][j];}cout<<"\n";}}
