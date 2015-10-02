#include <iostream>
#include <vector>
#include "tools.h"
#include "insertion_sort.h"
#include "quick_sort.h"

int main()
{
    std::vector<int> v = {2 , 4 , 1 , 9 , 10} ;
    int nums[] = {2 , 4 , 1 , 9 , 10} ;
    /**** insertion sort ****
    insertion_sort(v.begin() , v.end()) ;

    insertion_sort(std::begin(nums) , std::end(nums)) ;
    ****/
    
    quick_sort_v_base(v.begin() , v.end()) ;
    quick_sort_v_base(std::begin(nums) , std::end(nums)) ;

    print(v.begin() , v.end()) ;
    print(std::begin(nums) , std::end(nums)) ;
}
