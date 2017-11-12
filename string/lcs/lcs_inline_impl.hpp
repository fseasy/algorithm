#include "lcs.h"
namespace algorithm_impl {
namespace string {

inline
int LCS::naive_lcs(const std::string &s1, const std::string &s2) {
    return naive_lcs_impl(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend());
}

template<typename BidirectionalIt1, typename BidirectionalIt2>
inline
int LCS::lcs(BidirectionalIt1 s1_first, BidirectionalIt1 s1_last,
             BidirectionalIt2 s2_first, BidirectionalIt2 s2_last) {
    using std::vector;
    if (s1_first == s1_last || s2_first == s2_last) {
        return 0;
    }
    auto s1_len = std::distance(s1_first, s1_last);
    auto s2_len = std::distance(s2_first, s2_last);
    // based on 0 -> lcs[m, n] = table[m-1][n-1]
    vector<vector<int>> dp_table(s1_len, vector<int>(s2_len, 0));
    // set edge
    dp_table[0][0] = *s1_first == *s2_first ? 1 : 0;
    for (auto i = 1UL; i < s1_len; ++i) {
        dp_table[i][0] = *(s1_first + i) == *s2_first ? 1 : dp_table[i - 1][0] ;
    }
    for (auto i = 1UL; i < s2_len; ++i) {
        dp_table[0][i] = *s1_first == *(s2_first + i) ? 1 : dp_table[0][i - 1];
    }
    // set others slots
    for (auto row_id = 1UL; row_id < s1_len; ++row_id) {
        for (auto col_id = 1U; col_id < s2_len; ++col_id) {
            if (*(s1_first + row_id) == *(s2_first + col_id)) {
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
} // end of namespace algorithm impl
