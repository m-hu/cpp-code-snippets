#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; if(!(cin>>s)) return 0;
    int n=s.size();
    int i=0;
    while(i<n){
        int best_len=0, best_off=0;
        for(int j=0;j<i;j++){
            int len=0;
            while(i+len<n && j+len<i && s[j+len]==s[i+len]) len++;
            // Also allow overlapping: j+len can be >= i, we can still extend if s[j+len % ...]
            // For standard LZ77 sliding window, we check s[j+len]==s[i+len] as long as j+len < n and i+len < n
            // Actually the window is s[0..i-1], so j+len must stay in window for non-overlap,
            // but overlapping extension is valid in LZ77: we compare s[j+len] with s[i+len] where j+len may be >= i
            // For simplicity, use direct comparison within s:
            // Recompute with overlap allowed via s[j+len]==s[i+len] for j+len < n
            // Reset and redo:
            len=0;
            while(i+len<n && j+len<n && s[j+len]==s[i+len]) len++;
            if(len>best_len){ best_len=len; best_off=i-j; }
        }
        if(best_len==0){
            cout << 0 << " " << 0 << " " << s[i] << "\n";
            i++;
        } else {
            char nxt = (i+best_len < n) ? s[i+best_len] : '$';
            cout << best_off << " " << best_len << " " << nxt << "\n";
            i += best_len + (i+best_len < n ? 1 : 0);
            if(best_len>0 && i> n) break;
            if(i==n && best_len>0){
                // last factor was exact match to end, already handled
                break;
            }
        }
    }
    return 0;
}
