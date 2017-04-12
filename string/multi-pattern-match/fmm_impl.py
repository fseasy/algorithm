#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import bisect
from trie import Trie
from len2set import Len2WordSet

class FMMObj(object):
    TRIE = 0
    LEN2SET = 1
    VALID_TYPE = set([TRIE, LEN2SET])
    def __init__(self, structure_type=TRIE):
        if structure_type == self.TRIE:
            self._match_obj = Trie()
        elif structure_type == self.LEN2SET:
            self._match_obj = Len2WordSet()
        else:
            raise ValueError("unknow structure type: {}".format(structure_type))
        self._type = structure_type

    def _add_word_list4trie(self, word_list):
        for word in word_list:
            self._match_obj.insert_word(word)

    def _add_word_list4len2set(self, word_list):
        for word in word_list:
            self._match_obj.add_word(word)

    def add_word_list(self, word_list):
        '''
        add word list to match obj word.
        @return None
        '''
        if self._type == self.TRIE:
            return self._add_word_list4trie(word_list)
        elif self._type == self.LEN2SET:
            return self._add_word_list4len2set(word_list)

    def _match_by_trie(self, text):
        '''
        using trie to match
        '''
        i = 0
        text_len = len(text)
        range_list = []
        while i < text_len:
            w = self._match_obj.max_match(text[i:])
            if len(w) == 0:
                i += 1
            else:
                end_pos = i + len(w)
                range_list.append((i, end_pos))
                i = end_pos
        return range_list 

    def _match_by_len2set(self, text):
        '''
        using len2set to match
        '''
        ascending_len_list = self._match_obj.get_ascending_len_list()
        pos = 0
        text_len = len(text)
        word_range_list = []
        while pos < text_len:
            left_len = text_len - pos
            # bisect.bisect(list, value)
            # return the index of the element which is the first that `bigger` than value
            # so the value at `index - 1` of list equals of less than value
            # do following logic, we get the valid sub-searching-length-list
            biggest_valid_len_index = bisect.bisect(ascending_len_list, left_len) - 1
            search_len_index = biggest_valid_len_index
            while search_len_index >= 0:
                # in descending length search
                word_len = ascending_len_list[search_len_index]
                token = text[pos: pos + word_len]
                wordset = self._match_obj[word_len]
                if token in wordset:
                    # found.
                    word_range_list.append((pos, pos + word_len))
                    pos = pos + word_len
                    break
                search_len_index -= 1
            else:
                # not found at this pos
                pos += 1
        return word_range_list 


    def match(self, text):
        '''
        match word for input text, return the match range list
        @return list, range list, like [(s1, e1), ...]
        '''
        if self._type == self.TRIE:
            return self._match_by_trie(text)
        elif self._type == self.LEN2SET:
            return self._match_by_len2set(text)
        else:
            raise ValueError("unknow structure type in match function")

def __unittest():
    trie_obj = FMMObj(FMMObj.TRIE)
    len2set_obj = FMMObj(FMMObj.LEN2SET)

    word_list = [
          u"天气",
          u"晴空",
          u"晴朗",
          u"气候",
          u"北京",
          u"京城",
          u"周末"
    ]
    trie_obj.add_word_list(word_list)
    len2set_obj.add_word_list(word_list)

    text = u"北京城天气晴朗"
    print(trie_obj.match(text))
    print(len2set_obj.match(text))
    assert(trie_obj.match(text) == len2set_obj.match(text))

if __name__ == "__main__":
    __unittest()
