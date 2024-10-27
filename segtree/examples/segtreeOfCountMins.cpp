#ifndef DO_NOT_INCLUDE_SYS_LIBS

#include <bits/stdc++.h>

#endif // DO_NOT_INCLUDE_SYS_LIBS

#include "segtree.h"

using namespace std;
namespace addstd {};
using namespace addstd;

#define int long long

pair <int, int> countOfMins(const pair <int, int> &a, const pair <int, int> &b) {
    if (a.first == b.first) {
        return {a.first, a.second + b.second};
    }
    
    return (a.first < b.first? a: b);
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    segtree <pair <int, int> > st(n, make_pair(1000000000000LL, 1000000000000LL), countOfMins);
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        st.set(i, make_pair(a, 1));
    }
    
    for (int i = 0; i < m; ++i) {
        int o;
        cin >> o;
        
        if (o == 1) {
            int i, v;
            cin >> i >> v;
            
            st.set(i, make_pair(v, 1));
        }
        else {
            int l, r;
            cin >> l >> r;
            
            pair <int, int> p = st.get(l, r);
            cout << p.first << " " << p.second << "\n";
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

