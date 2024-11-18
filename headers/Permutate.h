#include <iostream>
#include <vector>
#include <algorithm>

void Permutate(const char ArrayOfChars[], std::string& prefix, const int _sizeOfArray, const int slots, std::vector<std::string>& result, const int allowedBonds)
{
    if (slots == 0)
    {
        int countOnes = std::count(prefix.begin(), prefix.end(), '1');
        
        if (std::find(result.begin(), result.end(), prefix) == result.end() && countOnes <= allowedBonds)
        {
            result.push_back(prefix);
        }
        return;
    }

    for (int i = 0; i < _sizeOfArray; i++)
    {
        // for now let's avoid consecutive double bonds
        if (prefix.empty() || !(prefix.back() == '1' && ArrayOfChars[i] == '1'))
        {
            prefix.push_back(ArrayOfChars[i]);
            Permutate(ArrayOfChars, prefix, _sizeOfArray, slots - 1, result, allowedBonds);
            prefix.pop_back();
        }
    }
}
