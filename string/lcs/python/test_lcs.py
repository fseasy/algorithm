#!/usr/bin/env python
# -*- coding: gb18030 -*-
"""test lcs
"""

import unittest
import lcs

class TestLCS(unittest.TestCase):
    """test lcs
    """
    def test_lcs_count(self):
        """lcs count test
        """
        lcs_count = lcs.lcs_count

        a = "ba"
        b = ""
        self.assertEqual(lcs_count(a, b), 0)
        
        a = "ba"
        b = "a"
        self.assertEqual(lcs_count(a, b), 1)
        b = "a"
        self.assertEqual(lcs_count(a, b), 1)

        a = ["info", "box", "is", "so", "big"]
        b = ["the", "info", "box", "seems", "too", "big", "?"]
        self.assertEqual(lcs_count(a, b), 3)

        pair_list = [
            ("abc", "ac"),
            ("bcdae", "km"),
            ("bcdae", "ca"),
            ("bacbkmf", "bckm")
        ]
        target_val = [
            2,
            0,
            2,
            4
        ]
        for pair, v in zip(pair_list, target_val):
            self.assertEqual(lcs_count(*pair), v)


if __name__ == "__main__":
    unittest.main()
