#include <string>
#include <vector>
namespace algorithmImpl{

void buildLPS(vector<int> &LPS, const std::string& pattern, int patLen)
{
    LPS[0] = 0;
    int currentMatchedLen = 0;
    for(int i = 1; i < patLen; ++i)
    {
        while(currentMatchedLen > 0 && pattern[i] != pattern[currentMatchedLen])
        {
            currentMatchedLen = LPS[currentMatchedLen - 1];
        }
        if(pattern[i] == pattern[currentMatchedLen])
        {
            ++currentMatchedLen;
        }
        LPS[i] = currentMatchedLen;
    }
}

size_t findKMP(const std::string& str, const std::string &pattern)
{
    int patLen = pattern.length(),
        strLen = str.length();
    if(patLen == 0 || strLen < patLen){ return -1; }
    vector<int> LPS(patLen); // Longest Proper Prefix wich is also Suffix (length)
    buildLPS(LPS, pattern, patLen);
    int currentMatchedLen = 0;
    for(int i = 0; i < strLen; ++i)
    {
        while(currentMatchedLen > 0 && str[i] != pattern[currentMatchedLen])
        {
            currentMatchedLen = LPS[currentMatchedLen - 1];
        }
        if(str[i] == pattern[currentMatchedLen]){ ++currentMatchedLen; }
        if(currentMatchedLen == patLen)
        {
            // if need match next -> curretnMatchedLen = LPS[currentMatchedLen - 1] 
            return i - patLen + 1;
        }
    }
    return -1;
}

} // end of namespace algorithmImpl

using algorithmImpl::findKMP;
