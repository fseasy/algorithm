#include <iostream>
#include <tuple>
#include <cassert>

#include "lcs.h"

void test(){
    using std::vector;
    using std::string;
    using std::tuple; // pair is enough, just test.
    using std::make_tuple;
    using namespace algorithm_impl::string;

    vector<tuple<string, string>> test_pairs = {
        make_tuple("", ""),
        make_tuple("", "a"),
        make_tuple("abc", "ac"),
        make_tuple("bcdae", "km"),
        tuple<string, string>{"bcdae", "ca"},
        tuple<string, string>{"bacbkmf", "bckm"}
    };
    for(const auto& str_pair : test_pairs) {
        const string& s1 = std::get<0>(str_pair);
        const string& s2 = std::get<1>(str_pair);
        int naive_result = LCS::naive_lcs(s1, s2);
        int dp_result = LCS::lcs(s1, s2);
        if (naive_result != dp_result) {
            std::cout << s1 << "\n" << s2 << "\n"
                      << "naive lcs = " << naive_result << "\n"
                      << "dp lcs = " << dp_result << "\n";
            exit(1);
        }
    }

}

int main() {

    using namespace std;

    string s1 = "abcd";
    string s2 = "bd";
    test();
    cerr << "all pass" << endl;

    return 0;
}