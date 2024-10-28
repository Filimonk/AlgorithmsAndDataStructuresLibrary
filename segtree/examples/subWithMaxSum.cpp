#ifndef DO_NOT_INCLUDE_SYS_LIBS

#include <bits/stdc++.h>

#endif // DO_NOT_INCLUDE_SYS_LIBS

#include <segtree.h>

using namespace std;
namespace addstd {};
using namespace addstd;

#define int long long

struct Node {
    int ans, suf, pref, sum;
} nullNode = {0, 0, 0, 0};

Node recount(const Node& a, const Node& b) {
    int ans = max(max(a.ans, b.ans), a.suf + b.pref);
    int suf = max(b.suf, a.suf + b.sum);
    int pref = max(a.pref, b.pref + a.sum);
    int sum = a.sum + b.sum;
    
    return (Node) {ans, suf, pref, sum};
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    segtree <Node> st(n, nullNode, recount);
    
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        st.set(i, (Node) {max(0LL, a), max(0LL, a), max(0LL, a), a});
    }
    
    cout << st.get(0, n).ans << "\n";

    for (int i = 0; i < m; ++i) {
        int ind, v; cin >> ind >> v;
        st.set(ind, (Node) {max(0LL, v), max(0LL, v), max(0LL, v), v});
        
        cout << st.get(0, n).ans << "\n";
    }
}

int32_t main() {
ios::sync_with_stdio(false);
cin.tie(0);

//freopen("input.txt", "r", stdin);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
