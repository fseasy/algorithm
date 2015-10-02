/**********************************************************
 * Author        : xu wei
 * Email         : readonlyfile@hotmail.com
 * Create time   : 2015-10-02 14:04
 * Last modified : 2015-10-02 14:04
 * Filename      : quick_sort.h
 * Description   : Quick sort - base version , implementation(maybe it is just copy) from wikipedia : https://en.wikipedia.org/wiki/Quicksort  
 * *******************************************************/

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
