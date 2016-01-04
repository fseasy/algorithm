#coding=utf8

import heapq

class MinHeap(object) :
    def __init__(self) :
        self.data = []

    def push(self , item) :
        heapq.heappush(self.data , item )

    def pop(self) :
        return heapq.heappop(self.data)
    
    def empty(self) :
        return self.__len__() == 0

    def has_same(self , checking_item , check_same_func=cmp) :
        same_ele = None 
        for ele in self.data :
            if check_same_func(checking_item , ele) == True :
                same_ele = ele
                break
        return True if same_ele is not None else  False
    
    def size(self) :
        return len(self.data)
    
    def __len__(self) :
        return len(self.data)
