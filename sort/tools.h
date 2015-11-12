/**********************************************************
 * Author        : xu wei
 * Email         : readonlyfile@hotmail.com
 * Create time   : 2015-10-02 14:57
 * Last modified : 2015-10-02 14:57
 * Filename      : tools.h
 * Description   : some tools function 
 * *******************************************************/
#ifndef __TOOLS_INCLUDED__
#define __TOOLS_INCLUDED__

#include <iostream>

bool fill_array_with_static_random_numbers(int A[] , int size , int low=1 , int heigh=100)
{
    int range = heigh - low ;
    if(range <= 0) return false ;
    //srand(999) ; // if we use a static number , it will get  a static random number sequence ! 
    for(size_t i = 0 ; i < size ; ++i)
    {
        int rand_tmp = rand() % range ;
        A[i] = rand_tmp + low ;
    }
    return true ;
}

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

template <typename RandomAccessIterator>
inline bool is_increasing(RandomAccessIterator first , RandomAccessIterator last)
{
    if(first == last) return false ;
    while(first != (last -1) )
    {
        if( *(first + 1 ) < *first ) return false ;
        ++first ;
    }
    return true ;
}

template <class RandomAccessIterator1 , class RandomAccessIterator2>
inline RandomAccessIterator2 __copy_backward(RandomAccessIterator1 first , RandomAccessIterator1 last , 
                                             RandomAccessIterator2 result)
{
    while(last != first) *--result = *--last ;
    return result ;
}
#endif
