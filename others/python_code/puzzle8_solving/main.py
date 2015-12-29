#coding=utf8

import logging
from minheap import MinHeap
from state import Puzzle8State

logging.basicConfig(level=logging.INFO)

def a_star_search(init_state , target_state) :
    heap = MinHeap()
    heap.push(init_state)
    print '++++++++++++++'
    cnt = 0
    while True :
        if heap.empty() :
            logging.info("Heap has been Empty . Stop")
            break
        cnt += 1
        cur_state = heap.pop()
        if cur_state.is_same2other_state(target_state) :
            logging.info("Get solving .")
            print cur_state
            print cnt
            break
        states_lst = cur_state.expand_states()
        for state in states_lst : 
            state.set_cost4a_star(target_state)
            if not heap.has_same(state) :
                heap.push(state)
        if cnt%1000 == 0 :
            print heap.size()
            print cur_state
def main() :
    init_puzzle_data_1d = [2,3,5,1,4,6,8,7]
    init_blank_row = 1
    init_blank_col = 3
    init_state = Puzzle8State()
    init_state.init_puzzle_data(init_puzzle_data_1d , init_blank_row , init_blank_col)

    target_puzzle_data_1d = [1,2,3,8,4,7,6,5]
    target_blank_row = 2
    target_blank_col = 2
    target_state = Puzzle8State()
    target_state.init_puzzle_data(target_puzzle_data_1d , target_blank_row , target_blank_col)
    
    print init_state
    print target_state
    print init_state._predict_score2target_state(target_state)
    a_star_search(init_state , target_state)

if __name__ == "__main__" :
    main() 
