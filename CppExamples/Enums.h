#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace EnumExamples
{
    //
    // Strongly-typed enums 
    // 
    // - declared using enum class
    // - not automatically converted to integers
    enum class Colors
    {
        Red = 1,
        Green,
        Blue
    };

    enum class CMYK
    {
        Cyan,
        Magenta,
        Yellow,
        Black
    };

    // Provide the underlying type of an enum value.
    enum class TestEnum : unsigned long
    {
        V1,
        V2,
        V3
    };


    //
    // Named enums
    //
    // Declare a named enum. 'Opcode' is a type. LDA, STA, PHA are of type 'Opcode'.
    // The values LDA, STA, PHA are accessible globally.
    enum Opcode
    {
        LDA,
        STA,
        PHA
    };

    // Declare a "no name" enum.
    enum { P1, P2, P3 };


    //
    // typedef enum
    //
    // Declare an enum using typedef.
    typedef enum { Running, Suspended, NotRunning } AppLifecycle;


    void Test()
    {
        //
        // Strongly-typed enums 
        // 
        // Create a variable of type Colors.
        Colors col = Colors::Blue;

        // Test the variable against an enum value.
        if (col == Colors::Blue)
            cout << "Blue ";

        // It is not possible to compare enumeration values from different enumeration types.
        // if (col == CMYK::Black) {} // does not compile


        //
        // Named enums
        //
        Opcode code = LDA;

        switch (code)
        {
        case LDA:
            cout << "LDA ";
            break;
        case STA:
            cout << "STA ";
            break;
        case PHA:
            cout << "PHA ";
            break;
        }


        //
        // typedef enums
        //
        AppLifecycle app1 = Running;
        AppLifecycle app2 = Suspended;

        // Automatically converted to int.
        cout << app1 << " "; // 0
        cout << app2 << " "; // 1
    }
}