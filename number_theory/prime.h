/**
*@file prime.h
*@brief some algorithm to generate prime number . 
*
*@author Xu , wei (readonlyfile@hotmail.com)
*date 2015-10-22
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <new>

/**
*    @brief Normal linear generate prime number
*    @param[in]  N :  int , the number range [2 , N )
*    @param[out] rst : vector<int> , for storing prime number result
*    @return : true or false 
*    @retval false : memory alloc failed
*    @retval true : ok
**/
bool normal_linear_generate_prime(int N , std::vector<int> & rst) ;

/**
*   @brief Normal linear generate prime number
*   @param[in]  N :  int , the number range [2 , N )
*   @param[out] rst : vector<int> , for storing prime number result
*   @return : true or false 
*   @retval false : memory alloc failed
*   @retval true : ok
**/
bool fast_linear_generate_prime(int N , std::vector<int> &rst) ;
/**
*   @brief  Whether the number is prime
*   @param[int] N : number
*   @return : true or false
**/
bool is_prime(int N) ;

/***implementation***/

bool normal_linear_generate_prime(int N , std::vector<int> & rst)
{
    std::vector<int> tmp_rst ;
    // we calc some thing about memory : 2^32 Bytes = 2^2 GB , so it may be necessary to alloc memory at heap .
    // Actually , we have to alloc memory dynamically , so `heap` is the only choice .
    bool * candidate_nums_is_prime = nullptr ;
    try
    {
        candidate_nums_is_prime = new bool[N] ;
    }
    catch(std::bad_alloc & ba)
    {
        std::cerr << "No such memory " << N << "Bytes to alloc !" << std::endl ;
        std::cerr << ba.what() << std::endl ;
        return false ;    
    }
    // sizeof(candidate_nums_is_prime) == 4
    std::memset(candidate_nums_is_prime , true , sizeof(bool) * N) ; 
    candidate_nums_is_prime[0] = false ;
    candidate_nums_is_prime[1] = false ;
    int sqrt_value = sqrt(N) ;
    for(int i = 2 ; i < N ; ++i)
    {
        if(!candidate_nums_is_prime[i]){ continue; } // skip when not a prime number
        tmp_rst.push_back(i);
        // filter
        if(i > sqrt_value + 1 ) continue ; // !! Attention ! If no this statements , the below i*i operation may be overflow !! 
                                           // ~~ which will cause wrong result !  
        for(size_t j = i*i ; j < N ; j += i)
        {
            candidate_nums_is_prime[j] = false ;
        }
    }
    rst.swap(tmp_rst) ;
    delete [] candidate_nums_is_prime ;
    
    return true ;
}

bool fast_linear_generate_prime(int N , std::vector<int> &rst)
{
    std::vector<int> tmp_rst ;
    size_t prime_cnt = 0 ;
    bool *candidate_nums_is_prime = nullptr ;
    try
    {
        candidate_nums_is_prime = new bool[N] ;
    }
    catch(std::bad_alloc & ba)
    {
        std::cerr << "No such memory " << N << "Bytes to alloc !" << std::endl ;
        std::cerr << ba.what() << std::endl ;
        std::cerr << "Exit!" << std::endl ;
        return false ;
    }
    std::memset(candidate_nums_is_prime , true , sizeof(bool) * N) ;
    candidate_nums_is_prime[0] = false ;
    candidate_nums_is_prime[1] = false ;
    for( int i = 2 ; i < N ; ++i)
    {
        if(candidate_nums_is_prime[i])
        {
            tmp_rst.push_back(i) ;
            ++prime_cnt ;
        }
        for(size_t j = 0 ; j < prime_cnt ; ++j)
        {
            int prime_factor = tmp_rst[j] ;
            int num_to_filter = i * prime_factor ;
            if(num_to_filter >= N) break ; 
            candidate_nums_is_prime[num_to_filter] = false ;
            if( i % prime_factor == 0) break ;
        }
    }
    rst.swap(tmp_rst) ;
    delete [] candidate_nums_is_prime ;
    return true ;
}

bool is_prime(int N)
{
    if(N <= 1 || N %2 == 0) return false ;
    int sqrt_value = sqrt(N) ;
    for(int factor = 3 ; factor <= sqrt_value ; factor += 2)
    {
        if(N % factor == 0 ) return false ;
    }
    return true ;
}

