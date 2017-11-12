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
    template<typename BidirectionalIt1, typename BidirectionalIt2>
    static int lcs(BidirectionalIt1 s1_first, BidirectionalIt1 s1_last,
                   BidirectionalIt2 s2_first, BidirectionalIt2 s2_last);
private:
    static int naive_lcs_impl(const std::string::const_iterator& s1_beg,
                              const std::string::const_iterator& s1_end,
                              const std::string::const_iterator& s2_beg,
                              const std::string::const_iterator& s2_end);

};


} // end of namespace string
} // end of namespace algorithm impl

// inline / template impl

#include "lcs_inline_impl.hpp"


#endif
