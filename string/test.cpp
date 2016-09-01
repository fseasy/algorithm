#include <iostream>
#include <string>
#include <functional>
#include <iomanip>
#include "find_rabinkarp.h"
#include "find_kmp.h"

using namespace std;

void testResult(const string&str, const string &pattern)
{
    static bool firstCall = true;
    if(firstCall)
    {
        cout << setw(15) << "find" 
             << setw(15) << "Rabin-Karp" 
             << setw(15) << "KMP" << endl;
        firstCall = false;
    }
    cout << setw(15) << static_cast<int>(str.find(pattern))
         << setw(15) << static_cast<int>(findRabinKarp(str, pattern)) 
         << setw(15) << static_cast<int>(findKMP(str, pattern)) << endl;
}

int main(int argc, char *argv[])
{
    string str = "Test sentence , it has some words.";
    string pattern1 = "sentence , it has some words.";
    string pattern2 = ", it";
    string pattern3 = "some work";
    auto test = bind(testResult, str, placeholders::_1);
    test(pattern1);
    test(pattern2);
    test(pattern3);
    return 0;
}
