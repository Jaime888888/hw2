#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** 
 * Converts a string containing multiple words into a set of individual keywords.
 * - Words are split at punctuation.
 * - Only words with at least 2 characters are included.
 */
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keywords;
    std::string currentWord;

    for (char c : rawWords)
    {
        if (isalnum(c))  // Keep alphanumeric characters
        {
            currentWord += c;
        }
        else  // Split at punctuation
        {
            if (currentWord.size() >= 2)
            {
                keywords.insert(convToLower(currentWord));  // Store in lowercase
            }
            currentWord.clear();
        }
    }

    // Add last word if it's valid
    if (currentWord.size() >= 2)
    {
        keywords.insert(convToLower(currentWord));
    }

    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
