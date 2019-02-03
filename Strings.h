#pragma once

#include <iostream>
#include <string>
#include <sstream> // ostringstream

using std::cout;
using std::endl;

namespace StringsExamples
{
    void StringOperations()
    {
        string s;

        // Convert a numerical value to a string.
        double d = 2.8;
        s = std::to_string(d); // to_string has nine overloads
        cout << s << " "; // 2.800000

        // Access the length of a string.
        s = "123456";
        cout << "len=" << s.length() << " "; // the length of std::string
        cout << "len=" << s.size() << " "; // the length of std::string
        char str[] = "123456";
        cout << "len=" << std::strlen(str) << " "; // the length of a C-string

        // Count characters in a string.
        s = "abcdec";
        auto n = count(begin(s), end(s), 'c');
        cout << "cnt=" << n << " "; // 2

        // Find the first occurence of a character in a string using string.find()
        s = "abcd ef gi"; // 4
        size_t firstIndex = s.find(' ');
        cout << firstIndex << " ";
        cout << s.substr(firstIndex + 1) << " "; // the substring after the first space: "ef gi"

        // Find the first occurrence of a character in a string using find().
        s = "abcdec";
        string::const_iterator ci = find(s.begin(), s.end(), 'c');
        if (ci != s.end()) // check if there are any Cs
            cout << *ci << " "; // 'c'

        // Replace a substring.
        s = "Hello there!";
        cout << s.substr(6, 5) << " "; // substr(index,length) - "there"
        s.replace(6, 5, "buba"); // replace(first,length,newstr) the replacement string need not be the same size as the substring that it is replacing
        cout << s << " ";

        // Initialize a variable to an empty string.
        s = string();
        cout << s << " ";
    }

    // Use StringStream to keep concatenated values.
    void ConcatenateValues()
    {
        // A buffer that will hold a string stream.
        std::ostringstream buffer;

        // Prepare the buffer by erasing it.
        buffer.str("");

        // Insert a few values to the buffer.
        buffer << 5 << " "
            << std::setiosflags(std::ios::fixed | std::ios::showpoint) << std::setprecision(4)
            << 3.56789 << " ";

        cout << buffer.str();
    }

    void CharType()
    {
        // Signed and unsigned char.
        signed char ch = -128;
        unsigned char uch = 255U;
        cout << "Signed=" << int(ch) << " ";
        cout << "Unsigned=" << int(uch) << " ";

        // Char to ASCII code conversion.
        cout << "ASCII('L')=" << std::dec << int('L') << "(dec) ";
        cout << "ASCII('L')=" << std::hex << int('L') << "(hex) ";

        // "Clean-up" after the 'hex' modifier to make the subsequent numbers decimal rather than hex.
        cout << std::dec;

        // Char arithmetic.
        cout << "'b'+1=" << 'b' + 1 << " ";
        cout << "char(' '+10)=" << char(' ' + 10) << " ";
    }

    void SaySomething(const char s[])
    {
        printf_s(s);
        printf_s(" ");
    }

    void CStyleStrings()
    {
        // A variable of type 'const char[]'
        const char cstr[] = "A ";

        SaySomething(cstr);

        // Conversion from char[] to char* (we lose the array size).
        char str[] = "B "; // str and &str[0] are equivalent
        char * pstr = str;

        SaySomething(pstr);

        // The length of C-style strings.
        // strlen(char[]) is the same as strlen(char*) 
        printf_s("%d ", strlen(str));  // strlen(char[])
        printf_s("%d ", strlen(pstr)); // strlen(char*)

        // Equality of C-style strings.
        const char * s1 = "AAA";
        const char * s2 = "AAA";

        // Compare values (the same).
        if (s1 == s2) cout << "TheSame ";

        // Compare references or pointers (different).
        if (&s1 != &s2) cout << "Different ";
    }

    void Test()
    {
        StringOperations();
        ConcatenateValues();
        CharType();
        CStyleStrings();
    }
}