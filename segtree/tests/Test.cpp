#ifndef DO_NOT_INCLUDE_SYS_LIBS

// Area for system headers

#endif // DO_NOT_INCLUDE_SYS_LIBS

#include "segtree.h"

using namespace std;
namespace addstd {};
using namespace addstd;

long long myFunc(long long &l, long long &r) {
    return 0;
}

int main() {
    segtree <int> st1(3, minOfSubsegment);
    st1.getTree();
    
    segtree <long long> st2(5, maxOfSubsegment);
    st2.getTree();
    
    st1.refresh(maxOfSubsegment);
    st1.getTree();
    
    st2.refresh(myFunc, 10LL);
    st2.getTree();
    
    segtree <int> st3(2);
    st3.getTree();
    
    return 0;
}
