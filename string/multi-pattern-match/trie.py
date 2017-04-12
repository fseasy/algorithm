#!/usr/bin/env
# -*- coding: utf-8 -*-

from __future__ import print_function

import logging

class _TrieNode(object):
    def __init__(self):
        # if word end in this node, _cnt++
        self._cnt = 0
        # if one word pass this node, _pass++
        self._pass_cnt = 0
        self._next = None

    @property
    def cnt(self):
        ''' cnt property
        '''
        return self._cnt
    
    @cnt.setter
    def cnt(self, value):
        '''cnt setter
        '''
        self._cnt = value
    
    @property
    def pass_cnt(self):
        ''' pass cnt property
        '''
        return self._pass_cnt

    @pass_cnt.setter
    def pass_cnt(self, value):
        '''pass cnt setter
        '''
        self._pass_cnt = value

    @property
    def next_data(self):
        ''' next property, avoid the standard name `next()` for iterator
        '''
        return self._next
    
    def get_next_node_may_create(self, char):
        '''
        get the next node of the char(index)
        if next is None or the index(char) not in next,
        ceate and add it!
        ATTENTION: no update for cnt and pass_cnt
        @return _TrieNode, the node for the index(char)
        '''
        if not self._next:
            self._next = dict()
        return self._next.setdefault(char, _TrieNode())

    def get_next_node(self, char):
        '''
        get the next node.
        if next is None or char not in the next,
        return None
        @return _TrieNode/None
        '''
        if not self._next:
            return None
        return self._next.get(char, None)

    def delete_next_node(self, char):
        '''
        delete the next node.
        @return True/False
        '''
        if char in self._next:
            del self._next[char]
            return True
        return False

class Trie(object):
    def __init__(self):
        self._root = _TrieNode()

    def insert_word(self, word):
        '''
        insert word to Trie.
        @return None
        '''
        word_len = len(word)
        if word_len == 0:
            # edge condition, can't using the following logic
            return
        node = self._root
        depth = 0
        while depth < word_len:
            node.pass_cnt += 1
            # storing the current char
            cur_char = word[depth] 
            node = node.get_next_node_may_create(cur_char)
            depth += 1
        node.cnt += 1

    def search_word(self, word):
        '''
        search word.
        @edge_condition if word is Empty, return False
        @return True/False
        '''
        word_len = len(word)
        if word_len == 0:
            # edge condition;
            # for Empty word, just return False
            return False
        node = self._root
        depth = 0
        while depth < word_len:
            char = word[depth]
            node = node.get_next_node(char)
            if node is None:
                return False
            depth += 1
        return node.cnt > 0 

    def max_match(self, text):
        '''
        from the start to index i, the token text[0: i+1] is the word with maximum length in the Trie
        @edge_condition text is Empty str, return ""
        @return Word/"", if matched, return the word with max matched, else return Empty string
        '''
        text_len = len(text)
        if text_len == 0:
            return ""
        max_matched_idx = -1 # the index is included!
        depth = 0
        node = self._root
        while depth < text_len:
            char = text[depth]
            node = node.get_next_node(char)
            if node is None:
                break
            elif node.cnt > 0:
                max_matched_idx = depth
            depth += 1
        return text[0: max_matched_idx+1]

    def delete_word(self, word2be_delete):
        '''
        delete word.
        post processing is a bit complex
        @return True/False
        '''
        word_len = len(word2be_delete)
        if word_len == 0:
            return False
        depth = 0
        node = self._root
        traversal_path = [node, ]
        while depth < word_len:
            char = word2be_delete[depth]
            node = node.get_next_node(char)
            # if node is None, None is pushed.
            # we can according to this to distinguish whether has found
            traversal_path.append(node)
            if node is None:
                break
            depth += 1
        last_node = node # ==> last_node = traversal_path[-1]
        if last_node is None or last_node.cnt <= 0:
            # not a word
            return False
        # del the word
        # the way to delete according to the situation of the word
        last_node_cnt = last_node.cnt # save the value(orignal value may be change)
        if last_node.pass_cnt > 0:
            # it is also a prefix. just set cnt = 0
            last_node.cnt = 0
            # pop the processed node
            traversal_path.pop()
        else:
            # leaf node
            # we can del the entrance

            # assert(len(traversal_path) >= 2)
            traversal_path.pop()
            previous_node = traversal_path[-1]
            last_char = word2be_delete[-1]
            previous_node.delete_next_node(last_char)
            previous_node.pass_cnt -= last_node_cnt # minus the pass cnt
            # MORE
            # delete the node in the path when pass_cnt equals 0 and cnt = 0
            negative_word_idx = -2
            while previous_node.pass_cnt <= 0 and previous_node.cnt <= 0:
                traversal_path.pop()
                if len(traversal_path) == 0:
                    # no node anymore, previous_node is the root node
                    break
                pp_node = traversal_path[-1]
                char = word2be_delete[negative_word_idx]
                pp_node.delete_next_node(char)
                negative_word_idx -= 1
                pp_node.pass_cnt -= last_node_cnt
                previous_node = pp_node
            # the last node in traversal path has been processed(minus last_node_cnt)
            if len(traversal_path) > 0:
                traversal_path.pop()
        # the left node havn't minus the last_node_cnt
        while len(traversal_path):
            node = traversal_path.pop()
            node.cnt -= last_node_cnt
        return True

    def traversal(self):
        '''
        traversal and storing the word as list
        @return list, all word list
        '''
        word_list = []
        # DFS
        stack = [ (self._root, "") ]
        while len(stack):
            node, word = stack.pop()
            # visit node
            if node.cnt > 0:
                # word!
                word_list.append(word)
            if node.next_data is None:
                continue
            for char, node in node.next_data.items():
                stack.append((node, word + char))
        return word_list




def _unittest_node():
    node = _TrieNode()
    node.cnt += 1
    print(node.cnt)

def _unittest():
    import sys

    trie = Trie()
    trie.insert_word("哈哈")
    trie.insert_word("哈皮")
    trie.insert_word("你好啊")

    assert(trie.search_word("哈哈") is True)
    assert(trie.search_word("哈皮") is True)
    assert(trie.search_word("你好啊") is True)
    assert(trie.search_word("你好") is False)
    assert(trie.search_word("哈2") is False)

    trie.insert_word("哈哈哈哈哈")
    
    assert(trie.max_match("哈哈哈哈") == "哈哈")
    assert(trie.max_match("哈哈哈哈哈") == "哈哈哈哈哈")
    assert(trie.max_match("哈哈哈哈哈哈") == "哈哈哈哈哈")
    assert(trie.max_match("不要哈哈") == "")
    assert(trie.max_match("哈一下") == "")

    word_list = trie.traversal()
    #for w in word_list:
    #    print(w)
    assert(sorted(word_list) == sorted(["哈哈", "哈皮", "你好啊", "哈哈哈哈哈"]))

    assert(trie.delete_word("哈哈哈哈哈") is True)
    assert(trie.max_match("哈哈哈哈") == "哈哈")
    assert(trie.max_match("哈哈哈哈哈") == "哈哈")
    assert(trie.max_match("哈哈哈哈哈哈") == "哈哈")
    assert(trie.max_match("不要哈哈") == "")
    assert(trie.max_match("哈一下") == "")
    
    assert(trie.delete_word("哈哈") is True)
    assert(trie.search_word("哈哈") is False)
    
    assert(trie.delete_word("哈哈") is False)
    
    word_list = trie.traversal()
    assert(sorted(word_list) == sorted(["哈皮", "你好啊"]))

    print("pass all", file=sys.stdout)

    

if __name__ == "__main__":
    _unittest()
