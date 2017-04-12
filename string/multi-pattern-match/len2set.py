#!/usr/bin/env python
# -*- coding: utf-8 -*-

class Len2WordSet(object):
    def __init__(self):
        self._len2set = dict()
        self._ascending_len_list = []
    
    def add_word(self, word):
        '''
        add word to len2set
        @return True/False
        '''
        word_len = len(word)
        if word_len == 0:
            return False
        word_set = self._len2set.setdefault(word_len, set())
        word_set.add(word)
        if len(self._len2set) > len(self._ascending_len_list):
            self._ascending_len_list = sorted(self._len2set.keys())
        return True

    def get_ascending_len_list(self):
        '''
        get ascending length list
        @return list, the length list
        '''
        return self._ascending_len_list

    def remove_word(self, word):
        '''
        remove word from len2set
        @return True/False
        '''
        word_len = len(word)
        if word_len == 0 or word_len not in self._len2set:
            return False
        word_set = self._len2set[word_len]
        #word_set.discard(word) # discard- no raise, remove raise error if no key
        if word in word_set:
            word_set.remove(word)
            return True
        else:
            return False

    def parse_from_file(self, word_file_path):
        '''
        parse from file
        '''
        with open(word_file_path) as input_f:
            for line in input_f:
                word = line.decode("utf-8").strip()
                self.add_word(word)

    def parse_from_word_list(self, word_list):
        '''
        parse form word list
        '''
        for word in word_list:
            self.add_word(word)

    def debug_output(self):
        '''
        debug output.
        '''
        for word_len in self._len2set:
            word_set = self._len2set[word_len]
            for word in word_set:
                print("{}, {}".format(word.encode("utf-8"), word_len))
   
    def __iter__(self):
        return self._len2set.__iter__()
    
    def __next__(self):
        return next(self.__iter__())

    def next(self):
        return self.__iter__().next()
    
    def __getitem__(self, idx):
        return self._len2set.__getitem__(idx)
    def __contains__(self, k):
        return self._len2set.__contains__(k)
    
    def setdefault(self, key, default):
        return self._len2set.setdefault(key, default)

    def keys(self):
        return self._len2set.keys()
    
    def items(self):
        return self._len2set.items()
