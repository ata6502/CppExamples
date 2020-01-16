#pragma once

#include <iostream>
#include <string>
#include <sstream> // ostringstream
#include <algorithm> // find_if_not
#include "Diagnostics.h"

using std::cout;
using std::endl;
using std::string;
using std::wstring;
using std::basic_string;

// string is a typedef for basic_string<char>.
// basic_string is a container that represents a sequence - the range of characters. 
// basic string in C++ is mutable, unlike strings in many other languages. 

// Both, basic_string<char> and basic_string<wchar> are platform specific:
// - if you're using the Visual C++ compiler, char is 8-bits and a wchar is 16-bits

// C++ 11 also introduced explicit and portable 16 and 32-bit typedefs of basic_string, 
// but basic_string<char> and basic_string<wchar> are sufficient in many cases. 

// Strings are implicitly null terminated and stored continuously. It means that their
// memory layout is compatible with C-style strings. We can get a pointer to the underlying string. 

// String compares the character sequences not the pointer addresses as would be the case for 
// a pair of C-style strings.

// String provides begin and end methods returning iterators pointing to the front and 
// the back of the string, not counting the null terminator. 

// You're free to add helper functions as non-member functions which is the preferred way 
// to add functionality in C++.

namespace StringsExamples
{
    // A non-member function that removes whitespaces from either end of a string.
    string Trim(string const & s)
    {
        // Find the first non-whitespace character - the front of the substring.
        // We use the isspace function as a predicate for the algorithm to use.
        auto front = std::find_if_not(begin(s), end(s), isspace);

        // Find the last whitespace character - to the back of the substring.
        auto back = std::find_if_not(rbegin(s), rend(s), isspace);

        // The front and back define the half-open range which we can use to define the substring to return. 
        // back is a reverse iterator pointing to the last whitespace character. We turn it into a regular 
        // iterator with the base() method returning the iterator's underlying base iterator. 
        return string{ front, back.base() };
    }

    void StringBasics()
    {
        // Bring the user-defined literal (suffix) "s". It's important to use the correct literals because 
        // the suffix "s" could mean "seconds" if we used chrono literals.
        using namespace std::string_literals; 

        // Raw string literals.
        auto rs1 = R"(aaa \ bbb " ccc)";
        auto rs2 = R"***(aaa )" bbb)***"; // you can use any delimiter you want; we used asterisks
        auto rs3 = R"(preserve
                      new
                      lines)"; // preserve\n                      new\n                      lines
        auto rs4 = R"(\\aaa\bbb\ccc\f.txt)";
        auto rs5 = R"(\\.\pipe\)"; // \\\\.\\pipe\\

        // Initialize a variable to an empty string.
        auto s = string(); // or string {};

        // Initialize a variable to std::string using the user-defined literal "s".
        // Without the suffix "s", the variable ss would be of type const char*.
        auto ss = "Hello"s;

        // Intialize a C-style string.
        auto sc = { "Hello" };

        // string is a typedef for basic_string<char>
        s = basic_string<char>{};

        // ... or the wide character version basic_string<wchar>
        auto ws = wstring{};

        ws = basic_string<wchar_t>{};

        // A character is almost always 1 byte.
        static_assert(sizeof(string::value_type) == 1, "1 byte");

        // A wide character is 2 bytes.
        static_assert(sizeof(wstring::value_type) == 2, "2 bytes");

        // Initialize a string with a string literal.
        s = string{ "hi" };

        ASSERT(!s.empty());
        ASSERT(s.size() == 2);

        // Get a pointer to the underlying string.
        cout << s.c_str() << " ";

        // Even when we initialize a string using the initializer list, 
        // the null terminator is added automatically.
        s = string{ 'a', 'b', 'c' };

        cout << s.c_str() << " ";

        // Remove all characters from the string.
        s.clear();

        // The string still needs to present the layout of an empty string rather than an empty container. 
        ASSERT(s.empty());                      // the string is empty
        ASSERT(s.size() == 0);                  // the string does not contain any characters
        ASSERT(strcmp(s.c_str(), "") == 0);     // the string can be passed it to a C-style API which assumes a valid null terminated string

        // Given a string...
        s = string{ "abcdef" };

        // ...we can obtain a substring.
        s = string(s, 2, 3); // starting with the 2nd position and spanning 3 characters 

        ASSERT(s == "cde");

        // String provides begin and end methods. Thanks to that we can use the range-for statement 
        // and enumerate the characters in the sequence.
        for (auto c : s)
            cout << c;
        cout << " ";

        // Concatenate strings.
        auto a = string{ "A" };
        auto b = string{ "B" };
        auto x = a + "@" + b;

        // Find the position of the @ symbol.
        auto pos = x.find('@');

        // Create a substring using the substr method.
        // Substr, by default, runs to the end of the source string.
        auto c = x.substr(pos);
        ASSERT(c == "@B");

        // Trim whitespaces using a custom function Trim.
        auto trimmed = Trim(" \t zzz \r\n ");
        ASSERT(trimmed == "zzz");
    }

    void StringOperations()
    {
        // Convert a numerical value to a string.
        double d = 2.8;
        auto s = std::to_string(d); // to_string has nine overloads
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

    // Use stringstream to put values separated by spaces into variables.
    // Useful when reading command-line parameters.
    void ReadValues()
    {
        string va, vb;

        // A sample string.
        string commandLine = "a b";

        std::stringstream ss(commandLine);
        ss >> va >> vb;

        cout << va << vb << " ";
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

    // C-style string is a an array char[]
    void CStyleStrings()
    {
        // A variable of type 'const char[]'
        const char cstr[] = "A ";

        SaySomething(cstr);

        // Conversion from char[] to char* (we lose the array size).
        char str[] = "B "; // str and &str[0] are equivalent
        char* pstr = str;

        SaySomething(pstr);

        // The length of C-style strings.
        // strlen(char[]) is the same as strlen(char*) 
        printf_s("%d ", strlen(str));  // strlen(char[])
        printf_s("%d ", strlen(pstr)); // strlen(char*)

        // Equality of C-style strings.
        const char* s1 = "AAA";
        const char* s2 = "AAA";

        // Compare values (the same).
        if (s1 == s2) cout << "TheSame ";

        // Compare references or pointers (different).
        if (&s1 != &s2) cout << "Different ";

        // Copy a C-style string. 
        // You can also use strcpy but remember about the null terminator.
        char dst[20];
        char src[] = "abcde"; // memory content: 'a' 'b' 'c' 'd' 'e' \0
        for (int i = 0; (dst[i] = src[i]) != '\0'; i++) // \0 is a null terminator
            ;
        cout << dst << " ";

        size_t len = strlen(src); // len=5 but remember that there is the 6th element at the end of src - the \0

        // Copy from std::string to a C-style string - DOES NOT WORK.
        //std::string t("hi");
        //char* s = new char[t.length() + 1]; // t.length() == a huge number
        //strcpy_s(s, t.size(), t.c_str()); // t.size() == 2, not the size in bytes
        //cout << s << " ";
        //delete[] s;
    }

    void Test()
    {
        StringBasics();
        StringOperations();
        ConcatenateValues();
        ReadValues();
        CharType();
        CStyleStrings();
    }
}