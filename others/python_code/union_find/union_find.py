# -*- coding: utf-8 -*-
"""Uion-Find, 并查集
impl according to 
https://blog.csdn.net/dm_vincent/article/details/7655764
"""

class _Node(object):
    """union-find set node
    """
    def __init__(self, e):
        self.val = e
        self.parent = e
        self._tree_size = 1

    @property
    def size(self):
        """The tree size. 
        if the node is not the tree, the value is useless.
        """
        if self.is_root():
            return self._tree_size
        else:
            return -1
    
    @size.setter
    def size(self, new_val):
        self._tree_size = new_val
    
    def is_root(self):
        """whether the node is a root node of a tree
        """
        return self.val == self.parent


class UnionFind(object):
    """UnionFind.
    support api:
    (1) is_connected(e1, e2)
    (2) connect(e1, e2)
    (3) get_union_set(e1) => get the whole union which e1 belong
    (4) get_all_union_set()
    
    impl the Weighted Quick-Union With Path Compression
    of https://blog.csdn.net/dm_vincent/article/details/7655764
    """

    def __init__(self, uniq_element_set):
        """given a uniq elemnet set and initialize a union find set.
        Args:
            uniq_element_set: a list of set, the target element. 
                element should support hash(), should be uniq. 
                because we'll index it directly use the element value self.
        """
        _uniq_set = set(uniq_element_set)
        if len(_uniq_set) != len(uniq_element_set):
            raise ValueError("target element set has duplicated values")
        self._element_info = {v: _Node(v) for v in _uniq_set}
    
    def _find_with_compress(self, e):
        """get e's root 
        and do compress.
        Returns:
            root-element: raw element value, not Node info
        """
        node_info = self._element_info[e] # if not in dict, just raise
        while not node_info.is_root():
            parent_val = node_info.parent
            parent_node_info = self._element_info[parent_val] 
            node_info.parent = parent_node_info.parent # compress 1 level
            node_info = parent_node_info
        return node_info.val
    
    def is_connected(self, e1, e2):
        """whethere element1 and element2 are connected
        Returns:
            True/False
        """
        parent1 = self._find_with_compress(e1)
        parent2 = self._find_with_compress(e2)
        return parent1 == parent2

    def connect(self, e1, e2):
        """connect e1 and e2
        """
        if self.is_connected(e1, e2):
            return 
        parent1_val = self._find_with_compress(e1)
        parent2_val = self._find_with_compress(e2)
        bigger_node = self._element_info[parent1_val]
        smaller_node = self._element_info[parent2_val]

        if bigger_node.size <= smaller_node.size:
            bigger_node, smaller_node = smaller_node, bigger_node
        bigger_node.size += smaller_node.size # add before change node1's parent
        smaller_node.parent = bigger_node.val
        
    def get_union_set(self, e):
        """get union set to which e blongs
        ATTENTION:
            the complexity may greater or equal O(NlgN).
            if we have a reverse pointer from the parent to the child, it may faster.
            but if we keep it, the _find_with_compress & connect will has more complexity.
            here we just keep the original design.

        Returns:
            a set of raw element.
        """
        union_set = set()
        # get current node path
        node_info = self._element_info[e]
        while not node_info.is_root():
            val = node_info.val
            union_set.add(val)
            parent_val = node_info.parent
            node_info = self._element_info[parent_val]
        # add parent node info
        union_set.add(node_info.val)
        # test the other node, from the leaf node
        for (val, node_info) in self._element_info.iteritems():
            history_val_list = []
            while not node_info.is_root():
                val = node_info.val
                if val in union_set: # quick break.
                    break
                history_val_list.append(val)
                parent_val = node_info.parent
                node_info = self._element_info[parent_val]
            # here node_info may be 
            # 1. node info where breaking => the history shoule be put to union-set
            # 2. node info of root => if root is in union_set, history_val_list shoule be put to set
            # we all can test the using the same logical.
            val = node_info.val
            if val in union_set:
                union_set.update(history_val_list)
        return union_set

    def get_all_union_set(self):
        """return all union set.
        
        Returns:
            a list of set.
        
        """
        already_processed_set = set()
        root2set = {}
        for (val, node_info) in self._element_info.iteritems():
            if val in already_processed_set:
                continue
            path_list = []
            while not node_info.is_root():
                # in fact, we can break early, but it may make code more ugly and complex
                # here we keep it more simple
                val = node_info.val
                path_list.append(val)
                parent_val = node_info.parent
                node_info = self._element_info[parent_val]
            path_list.append(node_info.val)
            root_val = path_list[-1]
            if root_val not in root2set:
                root2set[root_val] = set()
            root2set[root_val].update(path_list)
            already_processed_set.update(path_list)
        result = [root2set[key] for key in root2set]
        return result


