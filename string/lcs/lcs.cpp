#include "lcs.h"

namespace algorithm_impl {
namespace string {


int LCS::naive_lcs_impl(const std::string::const_iterator &s1_beg,
                        const std::string::const_iterator &s1_end,
                        const std::string::const_iterator &s2_beg,
                        const std::string::const_iterator &s2_end) {
    if (s1_beg == s1_end || s2_beg == s2_end) {
        return 0;
    }
    auto s1_last_char_iter = s2_end - 1;
    auto s2_last_char_iter = s2_end - 1;
    if (*s1_last_char_iter == *s2_last_char_iter) {
        return 1 + naive_lcs_impl(s1_beg, s1_last_char_iter, s2_beg,
                                  s2_last_char_iter);
    } else {
        return std::max(
            naive_lcs_impl(s1_beg, s1_end, s2_beg, s2_last_char_iter),
            naive_lcs_impl(s1_beg, s1_last_char_iter, s2_beg, s2_end));
    }
}

int LCS::lcs(const std::string &s1, const std::string &s2) {}

} // end of namespace string
} // end of namespace algorithm_impl
