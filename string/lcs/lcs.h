#ifndef ALGORITHM_STRING_LCS_LCS_H
#define ALGORITHM_STRING_LCS_LCS_H

#include <string>
#include <vector>

namespace algorithm_impl {
namespace string {

class LCS {
public:
	static int naive_lcs(const std::string& s1, const std::string& s2);
	static int lcs(const std::string& s1, const std::string& s2);
private:
    static int naive_lcs_impl(const std::string::const_iterator& s1_beg,
                              const std::string::const_iterator& s1_end,
                              const std::string::const_iterator& s2_beg,
                              const std::string::const_iterator& s2_end);

};

inline
int LCS::naive_lcs(const std::string &s1, const std::string &s2) {
    return naive_lcs_impl(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend());
}


} // end of namespace string
} // end of namespace algorithm impl


#endif
