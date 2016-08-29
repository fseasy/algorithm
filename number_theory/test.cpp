#include <iostream>
#include "prime.h"

int main(int argc , char * argv[])
{
    if(argc < 2 )
    {
        std::cerr << "usage : " << argv[0] << " [number_up_bound]" << std::endl ;
        exit(1) ;
    }
    int max_range ;
    sscanf(argv[1] , "%d" , &max_range) ;
    std::vector<int> prime_nums ;
    if(argc == 3 && strcmp(argv[2] , "normal") == 0) normal_linear_generate_prime(max_range , prime_nums) ;
    else fast_linear_generate_prime(max_range , prime_nums) ; 
    //for(std::vector<int>::iterator ite = prime_nums.begin() ; ite != prime_nums.end() ; ++ite)
    //{
    //    std::cout << *ite << " " ;
    //    if(is_prime(*ite)) std::cout << "prime check ok" ;
    //    else std::cout << "prime check failed" ;
    //    std::cout << std::endl ; 
    //}
    std::cout << prime_nums.size() << " ";
    std::cout << prime_nums.back() ;
    std::cout << std::endl ;
}
