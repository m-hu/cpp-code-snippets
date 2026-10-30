#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin>>n)) return 0;
    vector<string> vote(n);
    for(int i=0;i<n;i++) cin>>vote[i];
    // 2PC: coordinator collects votes. Any NO or TIMEOUT => ABORT else COMMIT
    bool all_yes=true;
    for(int i=0;i<n;i++) if(vote[i]!="YES") all_yes=false;
    string decision=all_yes?"COMMIT":"ABORT";
    cout<<"DECISION: "<<decision<<"\n";
    for(int i=0;i<n;i++){
        string state;
        if(vote[i]=="TIMEOUT") state="ABORT";
        else state=decision;
        cout<<"P"<<i<<": "<<state<<"\n";
    }
    return 0;
}
