#include <iostream>
#include <vector>
#include "insertion_sort.h"

using namespace std ;

template <class T , size_t N>
constexpr size_t get_len(T (&)[N]) noexcept
{
    return N ;
}

int main()
{
    vector<int> v = {2 , 4 , 1 , 9 , 10} ;
    insertion_sort(v.begin() , v.end()) ;
    for(size_t i = 0 ; i < v.size() ; ++i) cout << v[i] << " " ;
}
