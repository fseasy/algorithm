#include <string>

namespace algorithmImpl{

using namespace std;

static unsigned RabinKarpAlphabetSize = 1 << (sizeof(char) * 8) ; // normally, this equals to 2^8 = 256.
static unsigned RabinKarpPrimeNumber = 16777213; // we need an big prime and statisfied '|alphabet| * prime <= 2^32' , 
                                                 // so  prime <= 2^32 / 256 = 2^24 = 16777216
                                                 // We use `Sieve of Eratosthenes` to get the max prime = 16777213.
inline bool isStrSubstringEqual2Pattern(const string &str, size_t substrStartPos, const string &pattern, size_t patternLen)
{
    // for efficiency, we use the duplicated parameter `patternLen`
    // But I'm worrying that the compiler will not inline it (has one loop)
    for(int i = 0; i < patternLen; ++i)
    { 
        if(str[substrStartPos + i] != pattern[i]){ return false; } 
    }
    return true;
}

// calc h^{m-1}
unsigned calcRabinKarpH(size_t pLenMinus1)
{
    if(pLenMinus1 == 0){ return 1; }
    else if(pLenMinus1 == 1){ return RabinKarpAlphabetSize % RabinKarpPrimeNumber; }
    unsigned long long halfVal = calcRabinKarpH(pLenMinus1 / 2U); // lifting to unsigned long long
    if( pLenMinus1 % 2 == 0)
    {
        return (halfVal * halfVal) % RabinKarpPrimeNumber;
    }
    else
    {
        return (((halfVal * halfVal) % RabinKarpPrimeNumber) * RabinKarpAlphabetSize) % RabinKarpPrimeNumber;
    }
}

size_t findRabinKarp(const string &str, const string &pattern)
{
    size_t sLen = str.size(),
           pLen = pattern.size();
    if(sLen < pLen){ return -1; } // edge condition (because we use size_t, so pLen <= sLen should be guaranteed)
    unsigned patternEncodingVal = 0,
             strEncodingVal = 0;
    size_t weight = calcRabinKarpH(pLen - 1);
    for(size_t i = 0; i < pLen; ++i)
    {
        // should cast `char` to `unsigned char` instead of `unsigned` (the latter leads to INT_MAX - charVal if charVal is a negative)
        // or use ( charVal & 0xff )
        patternEncodingVal = (patternEncodingVal * RabinKarpAlphabetSize + static_cast<unsigned char>(pattern[i])) % RabinKarpPrimeNumber;
        strEncodingVal = (strEncodingVal * RabinKarpAlphabetSize + static_cast<unsigned char>(str[i])) % RabinKarpPrimeNumber;
    }
    for(size_t s = 0; ; ++s) // exit condition is judge in inner
    {
        if(patternEncodingVal == strEncodingVal)
        {
            // encoding has match, but we have to check it char by char
            if(isStrSubstringEqual2Pattern(str, s, pattern, pLen)){ return s; }
        }
        else
        {
            // encoding next str substr
            size_t nextPos = s + pLen;
            if(nextPos >= sLen){ break; }
            // flowing is very important !
            // In <Introduction to Algorithm>, the formular is : minusHVal = ( strEncodingVal - weight * str[s] )
            // But there may be something wrong( we should always attention to operation minus(-) forUNSIGNED ) :
            //      if strEncodingVal is smaller than weight * str[s] , then the minus result is un-expected !!
            //      and Unfortunately, it leads to error encoding result. (we get error result in test case.)
            // It may be easy to find the problem, but how can we solved it ?
            // I find the solution at : https://www.programmingalgorithms.com/algorithm/rabin%E2%80%93karp-algorithm?lang=C%2B%2B
            // the answer is : 
            // using the divisor to minus the ( (weight * str[s]) % divisor ) , that leads to an positive result. and then add the strEncodingVal,
            // at last , we mod the divisor agagin. ==>
            // ====>
            //    ( strEncodingVal + ( RabinKarpPrimeNumber - (str[s] * weight) % RabinKarpPrimerNumber ) ) % RabinKarpPrimerNumber
            // according to the mod operation property : (a +/- b ) % M = (a%M  +/- b%M) % M
            // we can expand the above formula to :
            //    strEncodingVal % RabinKarpPrimerNumber + RabinKarpPrimerNumber % RabinKarpPrimerNumber - (str[s] * weight) % RabinKarpPrimerNumber
            // because we have : a % a = 0 , and strEncodingVal < RabinKarpPrimerNumber,  so we can get :
            // strEncodingVal - (str[s] * weight) % RabinKarpPrimerNumber
            // it is a bit different from the original fomula, but at last , we have to also mod RabinKarpPrimerNumber, so here it is ok.
            unsigned minusHVal = (RabinKarpPrimeNumber 
                                  - (static_cast<unsigned char>(str[s]) * weight) % RabinKarpPrimeNumber 
                                  + strEncodingVal) % RabinKarpPrimeNumber;
            strEncodingVal = (minusHVal * RabinKarpAlphabetSize + static_cast<unsigned char>(str[nextPos])) % RabinKarpPrimeNumber;
        }
    }
    return -1;
}


} // end of namespace algorithmImpl

using algorithmImpl::findRabinKarp;
