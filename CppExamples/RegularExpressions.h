#pragma once

#include <iostream>
#include <regex>

using std::cout;
using std::endl;
using std::regex;

namespace RegularExpressions
{
    void assert(bool condition)
    {
        if (!condition)
            cout << "ERROR ";
    }

    void RegexSearch()
    {
        auto s = string{ "AAA 808-2321 BBB" };

        // Use a raw string literal to avoid unnecessary escaping in the regular expression.
        // Add grouping to identify the individual parts of the string.
        auto r = regex{ R"((\d{3})-(\d{4}))" };

        // Define a match result object (a match container). It will be filled with matches and submatches
        // in a vector containing pairs of iterators.
        // If you want to match C-style strings, use std::cmatch instead of std::smatch.
        auto m = std::smatch{}; // the same as m = std::match_results<string::const_iterator> {};

        // No matches yet.
        assert(m.empty());

        // Perform a match:
        // s - a string to search called the target character sequence
        // m - match results
        // r - a regular expression applied to determine whether a match exists
        // regex_search returns true if a match exists.
        assert(std::regex_search(s, m, r));

        // Check if any match has been found.
        assert(!m.empty());

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
            // str holds a copy of the matched range - a substring. For large documents or many matches 
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
        // Our string to search. The valid filenames contained in the string: <abc.cc> and <www.txt>
        auto s = string{ "a.h qq <abc.cc> abc a,h ddd.exe <bb.exe > <s.d> dd..t <www.txt>" };

        // The regex_search function finds a single occurrence of a pattern. On the other hand, regular 
        // expression iterators continue iterating as the regular expression matches patterns repeatedly. 
        // They require bidirectional access to the sequence and avoid creating temporary string objects.

        // Define the regular expression that matches a filename contained within angle brackets.
        // The parentheses are for grouping and ensure that the filename is captured in a submatch.
        auto r = regex{ R"(<\w+\.\w{2,3}>)" };

        // Determine the the beginning and the end of the string to search.
        auto first = &*s.begin();
        auto last = first + s.length();

        // Iterate over a string using a regular expression iterator.
        // We are using the character string version of the iterator.
        // There is also an sregex_token_iterator.
        for (auto it = std::cregex_iterator{ first, last, r };
            it != std::cregex_iterator{};
            ++it)
        {
            // Dereference the iterator to return a match. In this case, we further index into 
            // the match to retrieve the first submatch - the filename.
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
