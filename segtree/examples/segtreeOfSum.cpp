#include <bits/stdc++.h>

#include "segtree.h"

using namespace std;
using namespace adstd;

#define int long long

void solve() {
    int n, m;
    cin >> n >> m;
    
    segtree <int> st(n);
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        st.set(i, a);
    }
    
    for (int i = 0; i < m; ++i) {
        int o;
        cin >> o;
        
        if (o == 1) {
            int i, v;
            cin >> i >> v;
            
            st.set(i, v);
        }
        else {
            int l, r;
            cin >> l >> r;
            
            cout << st.get(l, r) << "\n";
        }
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
