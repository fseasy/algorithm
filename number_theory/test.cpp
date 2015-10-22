#include <iostream>
#include "prime.h"

int main(int argc , char * argv[])
{
    int max_range = 0xFF ;
    std::vector<int> prime_nums ;
    if(argc == 2 && strcmp(argv[1] , "normal") == 0) normal_linear_generate_prime(max_range , prime_nums) ;
    else fast_linear_generate_prime(max_range , prime_nums) ; 
    for(std::vector<int>::iterator ite = prime_nums.begin() ; ite != prime_nums.end() ; ++ite)
    {
        std::cout << *ite << " " ;
        if(is_prime(*ite)) std::cout << "prime check ok" ;
        else std::cout << "prime check failed" ;
        std::cout << std::endl ; 
    }
    std::cout << std::endl ;
}
