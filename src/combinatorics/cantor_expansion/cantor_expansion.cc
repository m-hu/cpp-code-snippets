#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;
using int64 = long long;
int64 fact(int n) { int64 f = 1; for (int i = 2; i <= n; i++) f *= i; return f; }
int dval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return toupper(c) - 'A' + 10;
}
char dchar(int v) { return v < 10 ? (char)('0' + v) : (char)('A' + v - 10); }
string stripz(string s) {
    size_t p = s.find_first_not_of('0');
    if (p == string::npos) return "0";
    return s.substr(p);
}
string addBase(string X, string Y, int b) {
    string r;
    int i = (int)X.size() - 1, j = (int)Y.size() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int s = carry;
        if (i >= 0) s += dval(X[i--]);
        if (j >= 0) s += dval(Y[j--]);
        r.push_back(dchar(s % b));
        carry = s / b;
    }
    reverse(r.begin(), r.end());
    return stripz(r);
}
string mulBase(string X, string Y, int b) {
    X = stripz(X); Y = stripz(Y);
    if (X == "0" || Y == "0") return "0";
    vector<int> a, cc;
    for (int i = (int)X.size() - 1; i >= 0; i--) a.push_back(dval(X[i]));
    for (int i = (int)Y.size() - 1; i >= 0; i--) cc.push_back(dval(Y[i]));
    vector<int> r(a.size() + cc.size(), 0);
    for (size_t i = 0; i < a.size(); i++) for (size_t j = 0; j < cc.size(); j++)
        r[i + j] += a[i] * cc[j];
    int carry = 0;
    for (size_t i = 0; i < r.size(); i++) {
        int t = r[i] + carry;
        r[i] = t % b;
        carry = t / b;
    }
    while (carry) { r.push_back(carry % b); carry /= b; }
    string s;
    for (int i = (int)r.size() - 1; i >= 0; i--) s.push_back(dchar(r[i]));
    return stripz(s);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; if (!(cin >> mode)) return 0;
    if (mode == "E") {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) cin >> p[i];
        vector<int> L;
        int64 rank = 0;
        for (int i = 0; i < n - 1; i++) {
            int c = 0;
            for (int j = i + 1; j < n; j++) if (p[j] < p[i]) c++;
            L.push_back(c);
            rank += (int64)c * fact(n - 1 - i);
        }
        for (size_t i = 0; i < L.size(); i++) { if (i) cout << ' '; cout << L[i]; }
        cout << "\n" << rank << "\n";
    } else if (mode == "D") {
        int n; cin >> n;
        vector<int> L(n - 1);
        for (int i = 0; i < n - 1; i++) cin >> L[i];
        L.push_back(0);
        vector<int> avail(n);
        for (int i = 0; i < n; i++) avail[i] = i;
        for (int i = 0; i < n; i++) {
            if (i) cout << ' ';
            cout << avail[L[i]];
            avail.erase(avail.begin() + L[i]);
        }
        cout << "\n";
    } else if (mode == "A") {
        int b; string X, Y; cin >> b >> X >> Y;
        cout << addBase(X, Y, b) << "\n";
    } else {
        int b; string X, Y; cin >> b >> X >> Y;
        cout << mulBase(X, Y, b) << "\n";
    }
    return 0;
}
