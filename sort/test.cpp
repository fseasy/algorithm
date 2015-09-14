#include <iostream>
#include <vector>
#include "insertion_sort.h"

template <class T , size_t N>
constexpr size_t get_len(T (&)[N]) noexcept
{
    return N ;
}

template <typename RandomAccessIterator>
inline void print(RandomAccessIterator first , RandomAccessIterator last)
{
    if(first == last) return ;
    std::cout << *first  ;
    ++first ;
    while(first != last)
    {
        std::cout << " " << *first ;
        ++first    ;
    }
    std::cout << std::endl ;
}


int main()
{
    std::vector<int> v = {2 , 4 , 1 , 9 , 10} ;
    insertion_sort(v.begin() , v.end()) ;
    print(v.begin() , v.end()) ;

    int nums[] = {2 , 4 , 1 , 9 , 10} ;
    insertion_sort(std::begin(nums) , std::end(nums)) ;
    print(std::begin(nums) , std::end(nums)) ;
}
