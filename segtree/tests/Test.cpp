#include "segtree.h"

using namespace addstd;

long long myFunc(const long long &l, const long long &r) {
    return 0;
}

int main() {
    segtree <int> st1(3, minOfSubsegment);
    st1.getTree();
    
    segtree <long long> st2(5, maxOfSubsegment);
    st2.getTree();
    
    st1.refresh(maxOfSubsegment);
    st1.getTree();
    
    st2.refresh(10LL, myFunc);
    st2.getTree();
    
    segtree <int> st3(2);
    st3.getTree();
}
