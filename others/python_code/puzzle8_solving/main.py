#coding=utf8

from state import Puzzle8State

def a_star_search(init_state , target_state) :
    


def main() :
    init_puzzle_data_1d = [2,3,4,1,5,6,7,8]
    init_blank_row = 1
    init_blank_col = 1
    init_state = Puzzle8State()
    init_state.init_puzzle_data(init_puzzle_data_1d , init_blank_row , init_blank_col)

    target_puzzle_data_1d = [1,2,3,4,5,6,7,8]
    target_blank_row = 2
    target_blank_col = 2
    target_state = Puzzle8State()
    target_state.init_puzzle_data(target_puzzle_data_1d , target_blank_row , target_blank_col)

    a_star_search(init_state , target_state)
