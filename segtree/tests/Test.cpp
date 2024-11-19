#ifndef DO_NOT_INCLUDE_SYS_LIBS

// Area for system headers

#endif // DO_NOT_INCLUDE_SYS_LIBS

#include "segtree.h"

using namespace std;
namespace addstd {};
using namespace addstd;

void myFunc(long long& res, long long& l, long long& r) {
    res = min(l, r);
}

int main() {
    segtree <int> st1(3, minOfSubsegment);
    st1.set(0, 5);
    st1.getTree();
    cout << st1.get(0, 1) << "\n";
    
    segtree <long long> st2(5, maxOfSubsegment);
    st2.getTree();
    
    st1.refresh(maxOfSubsegment);
    st1.getTree();
    
    cout << "\n";
    st2.refresh(myFunc, 10LL);
    st2.set(0, 5);
    st2.getTree();
    long long ans;
    st2.get(ans, 0, 1);
    cout << ans << "\n";
    st2.get(ans, 1, 2);
    cout << ans << "\n";
    cout << "\n";
    
    segtree <int> st3(2);
    st3.getTree();
    
    return 0;
}
