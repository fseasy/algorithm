#include <iostream>

#include "lcs.h"

int main() {
    using namespace algorithm_impl::string;
    using namespace std;

    string s1 = "abcd";
    string s2 = "bd";

    cout << LCS::naive_lcs(s1, s2) << endl;
    
    return 0;
}