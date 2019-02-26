#pragma once

#include <iostream>
#include <regex>
#include "Diagnostics.h"

using std::cout;
using std::endl;
using std::regex;

namespace RegularExpressions
{
    void RegexSearch()
    {
        auto s = string{ "AAA 808-2321 BBB" };

        // An example of a regular expression.
        // We use a raw string literal to avoid unnecessary escaping in the regular expression.
        // We add some grouping to identify the individual parts of the phone number.
        auto r = regex{ R"((\d{3})-(\d{4}))" };

        // Define a match result object (a match container) that'll be filled with any matches and submatches.
        // The matches are a sequence of iterators - a vector of pairs of iterators.
        // The match object doesn't hold a copy of the result which means that it doesn't 
        // create unnecessary copies. Also, the source string needs to stick around for the iterators to remain valid. 
        // If you want to match C-style strings, use std::cmatch instead of std::smatch.
        auto m = std::smatch{}; // the same as m = std::match_results<string::const_iterator> {};

        // The results are empty.
        ASSERT(m.empty());

        // Perform a match:
        // s - the string to search called the target character sequence
        // m - the match results
        // r - the regular expression applied to determine whether a match exists
        // regex_search returns true if a match exists.
        ASSERT(std::regex_search(s, m, r));

        // Use the empty method to determine whether a match was found.
        ASSERT(!m.empty());

        // Display found submatches - the groupings in this case. 
        // Each submatch is a pair of iterators defining 
        // the range of characters in the string being searched. 
        // The first submatch contains the entire found string.
        // Output:
        // 8:808-2321 
        // 3:808
        // 4:2321
        for (auto& sm : m)
        {
            // str holds a copy of the range in question - a substring. For large documents or many matches 
            // it's better to avoid making the substring copies and use the iterators instead.
            //auto str = sm.str();

            // The length method calculates the distance between the first iterator and the second. 
            cout << sm.length() << ":" << sm << " ";
        }

        // Reformat the original string using the format method which has a syntax of its own:
        // $` - denotes the sequence preceding the match
        // $1, $2 - submatches
        // $' - denotes the sequence following the match
        // Output: AAA <808 2321> BBB
        auto output = m.format(R"($`<$1 $2>$')");

        cout << output.c_str() << " ";
    }

    void RegexIterators()
    {
        // Our string to search.
        auto s = string{ "a.h qq <abc.cc> abc a,h ddd.exe <bb.exe > <s.d> dd..t <www.txt>" };

        // The regex_search function finds a single occurrence of a pattern. In unstructured data it's tedious 
        // to use regex_search or regex_match because they match only one occurrence of a pattern.
        // Regular expression iterators solve that problem. They continue iterating as the regular expression 
        // matches patterns repeatedly. It requires bidirectional access to the sequence so it may not work for 
        // certain streams of data.
        // Also, the regular expression iterators avoid creating temporary string objects.

        // Define the regular expression that matches a filename contained within angle brackets. 
        // The parentheses are for grouping and ensure that the filename is captured in a submatch.
        auto r = regex{ R"(<\w+\.\w{2,3}>)" };

        // Determine the the beginning and the end of the string to search.
        auto first = &*s.begin();
        auto last = first + s.length();

        // Iterate over a string using a regular expression iterator.
        // We are using the character string version of the iterator.
        for (auto it = std::cregex_iterator{ first, last, r };
            it != std::cregex_iterator{};
            ++it)
        {
            // Assuming there's a match, we can dereference the iterator to return a match result object.
            // In this case we're further indexing into the match results to retrieve the first submatch,
            // the filename.
            auto& match = (*it)[0];

            cout << match.length() << ":" << match << " ";
        }
    }

    void Test()
    {
        RegexSearch();
        RegexIterators();
    }
}
