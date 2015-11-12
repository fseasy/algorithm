#include "tools.h"
template <class RandomAccessIterator>
void insertion_sort(RandomAccessIterator first , RandomAccessIterator last) ;

template <class RandomAccessIterator>
inline void __linear_insert(RandomAccessIterator first , RandomAccessIterator last) ;

template <class RandomAccessIterator , class T>
void __ungarded_linear_insert(RandomAccessIterator last , T value) ;

template <class RandomAccessIterator>
void insertion_sort(RandomAccessIterator first , RandomAccessIterator last)
{
    if(first == last)
    {
        // Invalid edge condition
        return ;
    }
    for(RandomAccessIterator i = first + 1 ; i != last ; ++i)
    {
        __linear_insert(first , i) ;  
    }
}

template <class RandomAccessIterator>
inline void __linear_insert(RandomAccessIterator first , RandomAccessIterator last)
{
    typename std::iterator_traits<RandomAccessIterator>::value_type value = *last ;
    if(value < *first)
    {
        // value should be at the first position
        // moving
        __copy_backward(first , last , last + 1 ) ;
        *first = value ;
    }
    else
    {
        __ungarded_linear_insert(last , value ) ;
    }
}


template <class RandomAccessIterator , class T>
void __ungarded_linear_insert(RandomAccessIterator last , T value)
{
    RandomAccessIterator pre = last - 1 ;
    while(value < *pre)
    {
        // moving data
        *last = *pre ;
        last = pre ;
        // continue finding
        --pre ;
    }
    // finded !
    *last = value ;
}
