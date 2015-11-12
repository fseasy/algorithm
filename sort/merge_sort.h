/* ******************************************************
 * Author        : xu wei
 * Email         : readonlyfile@hotmail.com
 * Create time   : 2015-11-12 17:37
 * Last modified : 2015-11-12 17:37
 * Filename      : merge_sort.h
 * Description   : Merge Sort -
                   1. implementation from wikipedia : https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F
 * *******************************************************/

template <typename RandomAccessIterator>
void merge_sort(RandomAccessIterator first , RandomAccessIterator last)
{
    // [first , last )
    if(first == last) return ;
    size_t len = last - first ;
    // malloc memery for storing result . For working and buffer
    typename std::iterator_traits<RandomAccessIterator>::value_type *working_list = new typename std::iterator_traits<RandomAccessIterator>::value_type[len] ;
    typename std::iterator_traits<RandomAccessIterator>::value_type *buffer_list = new typename std::iterator_traits<RandomAccessIterator>::value_type[len] ;
    __copy_backward(first , last , buffer_list + len) ;
    for(size_t merge_size = 1 ; merge_size < len ; merge_size *= 2 )
    {
        for(size_t merge_range_start = 0 ; merge_range_start < len ; merge_range_start += merge_size*2 )
        {
            size_t merge_range_end = std::min(len , merge_range_start + merge_size*2 ) ;
            /* WRONG !!! 下面的逻辑改变了有序排列的范围！！ 因为有序的部分只能是[ start , +  merge_size ] [ +merge_size , end ]
               下面的逻辑改变了中间的位置；从而使得新划分的区块变得不再有序了！！
               size_t merge_range_mid = merge_range_start + ( merge_range_end - merge_range_start ) / 2 ;
            */
            size_t merge_range_mid = std::min(len , merge_range_start + merge_size) ;
            size_t left_low = merge_range_start , 
                   left_high = merge_range_mid ,
                   right_low = left_high  ,
                   right_high = merge_range_end ,
                   working_pos = merge_range_start ;
            while(left_low < left_high && right_low < right_high)
            {
                if(buffer_list[left_low]< buffer_list[right_low])
                {
                    working_list[working_pos] = buffer_list[left_low] ;
                    ++left_low ;
                }
                else
                {
                    working_list[working_pos] = buffer_list[right_low] ;
                    ++right_low ;
                }
                ++working_pos ;
            }
            while(left_low < left_high)
            {
                working_list[working_pos] = buffer_list[left_low] ;
                ++left_low ;
                ++working_pos ;
            }
            while(right_low < right_high)
            {
                working_list[working_pos] = buffer_list[right_low] ;
                ++right_low ;
                ++working_pos ;
            }
        }
        // swap working list and buffer list
        std::swap(working_list , buffer_list) ;
    }
    // copy buffer result to origin input result
    __copy_backward(buffer_list , buffer_list + len , last ) ;
}

