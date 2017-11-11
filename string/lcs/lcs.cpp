#include "lcs.h"

#include <algorithm>

namespace algorithm_impl {
namespace string {


int LCS::naive_lcs_impl(const std::string::const_iterator &s1_beg,
                        const std::string::const_iterator &s1_end,
                        const std::string::const_iterator &s2_beg,
                        const std::string::const_iterator &s2_end) {
    if (s1_beg == s1_end || s2_beg == s2_end) {
        return 0;
    }
    auto s1_last_char_iter = s1_end - 1;
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

int LCS::lcs(const std::string &s1, const std::string &s2) {
    using std::vector;
    auto s1_len = s1.size();
    auto s2_len = s2.size();
    if (s1_len == 0 || s2_len == 0){
        return 0;
    }
    // based on 0 -> lcs[m, n] = table[m-1][n-1]
    vector<vector<int>> dp_table(s1_len, vector<int>(s2_len, 0));
    // set edge
    dp_table[0][0] = s1[0] == s2[0] ? 1 : 0;
    for (auto i = 1UL; i < s1_len; ++i) {
        dp_table[i][0] = s1[i] == s2[0] ? 1 : dp_table[i - 1][0] ;
    }
    for (auto i = 1UL; i < s2_len; ++i) {
        dp_table[0][i] = s1[0] == s2[i] ? 1 : dp_table[0][i - 1];
    }
    // set others slots
    for (auto row_id = 1UL; row_id < s1_len; ++row_id) {
        for (auto col_id = 1U; col_id < s2_len; ++col_id) {
            if(s1[row_id] == s2[col_id]) {
                dp_table[row_id][col_id] = 1 + dp_table[row_id - 1][col_id - 1];
            } else {
                dp_table[row_id][col_id] = std::max(dp_table[row_id][col_id - 1],
                    dp_table[row_id - 1][col_id]);
            }

        }
    }
    return dp_table[s1_len - 1][s2_len - 1];
}

} // end of namespace string
} // end of namespace algorithm_impl
