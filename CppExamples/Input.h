#pragma once

#include <iostream>
#include <string> // getline, strlen
#include <conio.h> // getch()

using std::cout;
using std::endl;
using std::string;

namespace InputExamples
{
    void GetLine()
    {
        //
        // Input a string into a C-style array.
        //
        // MAX is the maximum number of characters to be read including the terminating '\0'.
        const int MAX = 10;

        // str is an array that stores characters read from cin.
        char str[MAX]; 

        cout << "Enter a string of not more than 9 characters: ";

        // Read a string. '\n' stops the input process. It is not stored in str.
        std::cin.getline(str, MAX, '\n'); 

        cout << "The string '" << str << "' has " << strlen(str) << " characters." << endl;

        //
        // Input a string into a std::string variable using std::getline(std::cin, std::string).
        //
        string s;
        cout << "Enter a string: ";
        std::getline(std::cin, s);
        cout << "The string '" << s << "' has " << s.length() << " characters and its size is " << s.size() << "." << endl;

        //
        // Input a string up to the first whitespace.
        //
        cout << "Enter a string up to the first whitespace: ";
        std::cin >> s;
        cout << "The string '" << s << "' has " << s.length() << " characters." << endl;
        std::cin.seekg(0, std::ios::end); // clean the input buffer
        std::cin.clear();
    }

    void GetValues()
    {
        // Enter three integer values.
        int a, b, c;
        cout << "Enter three integer values: ";
        std::cin >> a >> b >> c;
        cout << "You entered: " << a << ", " << b << ", " << c << endl;
    }

    void WaitForKey()
    {
        cout << "Press any key...";
        char ch = _getch(); // proceeds immediately after pressing a key
        cout << endl << "You entered " << ch << endl;
    }

    void Test()
    {
        GetLine();
        GetValues();
        WaitForKey();
    }
}