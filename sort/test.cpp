#include <iostream>
#include <vector>
#include "tools.h"
#include "insertion_sort.h"
#include "quick_sort.h"

int main()
{
    const int ARRAY_SIZE = 10000 ;
    int nums[ARRAY_SIZE] ;
    fill_array_with_static_random_numbers(nums , ARRAY_SIZE , 1 , 10000) ;
    std::vector<int> v(std::begin(nums) , std::end(nums)) ;
    /**** insertion sort ****
    insertion_sort(v.begin() , v.end()) ;

    insertion_sort(std::begin(nums) , std::end(nums)) ;
    ****/
    
    /**** quick sort base version     
    quick_sort_v_base(v.begin() , v.end()) ;
    quick_sort_v_base(std::begin(nums) , std::end(nums)) ;
    ****/
    quick_sort_2pointer_swap(v.begin() , v.end()) ;
    quick_sort_2pointer_swap(std::begin(nums) , std::end(nums)) ;
    
    /**
    print(v.begin() , v.end()) ;
    print(std::begin(nums) , std::end(nums)) ;
    **/
    if(is_increasing(v.begin() , v.end())) std::cout << "vector sorted ok !" ;
    else std::cout << "vector sorted wrong !" ;
    std::cout << std::endl ;
    if(is_increasing(std::begin(nums) , std::end(nums))) std::cout << "array sorted ok !" ;
    else std::cout << "array sorted wrong !" ;
    std::cout << std::endl ;
}
