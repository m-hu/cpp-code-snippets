#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// Multi-precision long division (schoolbook / Knuth Alg D spirit, base 10).
string strip0(string s) {
    size_t p = s.find_first_not_of('0');
    if (p == string::npos) return "0";
    return s.substr(p);
}
int cmpn(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}
string subn(const string& a, const string& b) { // requires a >= b
    string r;
    int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
    while (i >= 0) {
        int d = (a[i] - '0') - carry - (j >= 0 ? b[j] - '0' : 0);
        if (d < 0) { d += 10; carry = 1; } else carry = 0;
        r.push_back((char)('0' + d));
        i--; j--;
    }
    reverse(r.begin(), r.end());
    return strip0(r);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string A, B; if (!(cin >> A >> B)) return 0;
    A = strip0(A); B = strip0(B);
    if (cmpn(A, B) < 0) { cout << "0\n" << A << "\n"; return 0; }
    string q, cur = "0";
    for (size_t k = 0; k < A.size(); k++) {
        cur = strip0(cur + A[k]);
        int cnt = 0;
        while (cmpn(cur, B) >= 0) { cur = subn(cur, B); cnt++; }
        q.push_back((char)('0' + cnt));
    }
    cout << strip0(q) << "\n" << cur << "\n";
    return 0;
}
