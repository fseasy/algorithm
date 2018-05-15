#!/usr/bin/env python
# -*- coding: gb18030 -*-
"""Test union find correctly.
"""

import unittest

import union_find

class TestUnionFind(unittest.TestCase):
    """test union find.
    """
    def test_correctness(self):
        raw_element = [
            "A", "B",
            "C", "D",
            "E"
        ]
        union_find_set = union_find.UnionFind(raw_element)
        self.assertFalse(union_find_set.is_connected("A", "B"))
        union_find_set.connect("A", "B")
        self.assertTrue(union_find_set.is_connected("A", "B"))

        union_find_set.connect("C", "D")
        self.assertEqual(
            union_find_set.get_union_set("C"),
            set(["C", "D"])
        )

        union_find_set.connect("A", "C")
        self.assertEqual(
            union_find_set.get_union_set("C"),
            set(["C", "D", "A", "B"])
        )

        all_union_set_list = union_find_set.get_all_union_set()
        all_union_set_list.sort(key=lambda v: len(v))
        self.assertEqual(
            all_union_set_list,
            [
                set(["E"]),                
                set(["A", "B", "C", "D"]),
            ]
        )


if __name__ == "__main__":
    unittest.main()