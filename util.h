#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>

/** 
 * Computes the intersection of two sets (elements common to both).
 * Runs in O(n log n) using set operations.
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result;
    typename std::set<T>::iterator it1 = s1.begin();
    typename std::set<T>::iterator it2 = s2.begin();

    while (it1 != s1.end() && it2 != s2.end())
    {
        if (*it1 < *it2)
        {
            ++it1;
        }
        else if (*it2 < *it1)
        {
            ++it2;
        }
        else
        {
            result.insert(*it1);
            ++it1;
            ++it2;
        }
    }
    return result;
}

/** 
 * Computes the union of two sets (all unique elements from both).
 * Runs in O(n log n) using set operations.
 */
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> result = s1; // Start with all elements of s1
    result.insert(s2.begin(), s2.end()); // Insert all elements of s2
    return result;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s);

// Removes any trailing whitespace
std::string &rtrim(std::string &s);

// Removes leading and trailing whitespace
std::string &trim(std::string &s);

#endif
