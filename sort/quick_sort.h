/**********************************************************
 * Author        : xu wei
 * Email         : readonlyfile@hotmail.com
 * Create time   : 2015-10-02 14:04
 * Last modified : 2015-10-02 14:04
 * Filename      : quick_sort.h
 * Description   : Quick sort - 
                   1. base version , implementation(maybe it is just copy) from wikipedia : https://en.wikipedia.org/wiki/Quicksort  
                   2. double pointer swap version , implementation from wikipedia : https://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F
                   3. STL
 * *******************************************************/

/******
Quick sort base version .
*******/
template <typename RandomAccessIterator>
void quick_sort_v_base(RandomAccessIterator first , RandomAccessIterator last)
{
    // [ first , last )
    
    if(first == last) return ;
    // using last to be the pivot 
    RandomAccessIterator pivot = last - 1 ;
    RandomAccessIterator boundary = first ;
    typename std::iterator_traits<RandomAccessIterator>::value_type pivot_value = *pivot ;
    for(RandomAccessIterator i = first ; i != last - 1 ; ++i)
    {
        if(*i <= pivot_value)
        {
            std::swap(*i , *boundary) ;
            ++boundary ; 
            // `boundary` is the boundary of smaller and bigger and at bigger part ; 
            //            else , is the pivot(end) , when the previous sequence is ordered already .  
            // `bondary`  是小于阈值和大于阈值的序列的边界点，且属于大于阈值的部分。
            //            但如果除阈值点（序列尾）外前面的序列都是有序，那么`boundary`就是阈值点。
        }
    }
    std::swap(*boundary , *pivot) ;
    
    // partition finished
    quick_sort_v_base(first , boundary ) ; // [first , boundary )
    quick_sort_v_base(boundary + 1 , last) ; // [boundary + 1 , last )
}

/******
Quick sort 2 pointer swap version
  ****/

template <typename RandomAccessIterator>
void quick_sort_2pointer_swap(RandomAccessIterator first , RandomAccessIterator last)
{
    if(first == last) return ;
    RandomAccessIterator pivot = last - 1 ;
    if(pivot == first) return ; // it means there just only one element , we can just return ; Certainly , we can ignore it with a still right result . But it may be dangerous 
    RandomAccessIterator left = first , right = pivot - 1 ;
    typename std::iterator_traits<RandomAccessIterator>::value_type pivot_value = *pivot ;
    while(left < right)
    {
        while(*left < pivot_value && left < right) ++left ;
        while(*right >= pivot_value && left < right) --right ;
        std::swap(*left , *right) ;
    }
    if( *left >= pivot_value)
    {
        std::swap(*left , *pivot) ;
    }
    else
    {
        ++left ;
    }
    quick_sort_2pointer_swap(first , left ) ;
    quick_sort_2pointer_swap(left + 1 , last) ;
}
