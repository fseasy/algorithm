#include <iostream>
#include <string>
#include "find.h"

using namespace std;

int main(int argc, char *argv[])
{
    string str = "Test sentence , it has some words.";
    string pattern1 = "sentence , it has some words.";
    string pattern2 = ", it";
    cout << "find result : " << str.find(pattern1) << " " << str.find(pattern2) << " " 
                             <<str.find("some work")<< endl
         << "rabin-karp result : " << findRabinKarp(str, pattern1) << " " << findRabinKarp(str, pattern2) << " "
                                   << findRabinKarp(str, "some work") << endl;

    return 0;
}
