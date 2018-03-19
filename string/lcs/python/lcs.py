# -*- coding: gb18030 -*-
"""Longest Common sequence COUNT.
"""

try:
    import xrange as range
except ImportError:
    pass

def lcs_count(a, b):
    """count lcs
    a, b is a sequence-like obj support len, indexing, and indexed value should support ==
    Returns
    ========
    int
    """
    len_a = len(a)
    len_b = len(b)
    if not len_a or not len_b:
        return 0
    dp_table = [
        [0 for _2 in range(len_b)]
        for _1 in range(len_a)
    ]
    # init dp_table[0][0]
    dp_table[0][0] = int(a[0] == b[0])
    # init dp_table[0][j]
    for j in range(1, len_b):
        if a[0] == b[j]:
            dp_table[0][j] = 1
        else:
            dp_table[0][j] = dp_table[0][j - 1]
    # init dp_table[i][0]
    for i in range(1, len_a):
        if a[i] == b[0]:
            dp_table[i][0] = 1
        else:
            dp_table[i][0] = dp_table[i-1][0]
    for i in range(1, len_a):
        for j in range(1, len_b):
            if a[i] == b[j]:
                dp_table[i][j] = 1 + dp_table[i - 1][j - 1]
            else:
                dp_table[i][j] = max(dp_table[i][j - 1], dp_table[i - 1][j])
    return dp_table[-1][-1]
