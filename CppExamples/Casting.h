#pragma once

#include <iostream>

using std::cout;
using std::endl;

namespace CastingExamples
{
    // static_cast is used to convert between related types:
    // - explicit cast supported by language: float-to-int, int-to-double, int-to-bool, etc.
    // - explicit cast supported by user-defined constructors or conversions
    // - an integer to an enumeration
    // - a pointer type to another pointer type in the same hierarchy (although dynamic_cast is recommended)
    // static_cast is compile-time only
    void StaticCast()
    {
        int n;

        // Cast float-to-int
        n = static_cast<int>(56.7f / 2.0f); // 28.35 truncated to 28
        n = static_cast<int>(4.9f); // 4.9 truncated to 4

        // Cast int-to-bool
        n = 1;
        bool b = static_cast<bool>(n);
    }

    // dynamic_cast is used in downcasting:
    // - pointer-to-object of one class to pointer-to-object of another class in the same inheritance hierarchy	
    // - reference-to-object of one class to reference-to-object of another class in the same inheritance hierarchy
    // - dynamic_cast is similar to C# 'is' operation
    // - you can use dynamic_cast only on a class with a virtual function
    //
    // If the cast doesn't make sense, dynamic_cast returns a nullptr (for the pointer version) or throws a bad_cast 
    // exception (for the reference version).
    //
    // The run-time type information is stored in the vtable of the object. Therefore, in order to use dynamic_cast,
    // your class must have at least one virtual method. If your class does not have a vtable, trying to use dynamic_cast will
    // result in a compiler error C2683: 'dynamic_cast' : 'MyClass' is not a polymorphic type.

    // You can perform the same casts down the inheritance hierarchy with a static_cast or reinterpret_cast.
    // The difference with dynamic_cast is that it performs run-time (dynamic) type checking, while static_cast and reinterpret_cast
    // performs the casting even if they are erroneous.

    // A simple class hierarchy for the dynamic_cast examples.
    class Shape { public: virtual void Draw() { } };
    class Circle : public Shape { public: void Draw() { cout << "Circle "; } };
    class Rect : public Shape { public: void Draw() { cout << "Rectangle "; } };

    // Draws the shape only if it is a circle.
    void DrawCircle(Shape * shape)
    {
        Circle * circle = dynamic_cast<Circle*>(shape); // downcast from Shape to Circle
        if (circle != nullptr)
        {
            circle->Draw();
        }
    }

    void DynamicCast()
    {
        Circle circle1;
        Rect rectangle1;
        Circle circle2;

        DrawCircle(&circle1);
        DrawCircle(&rectangle1);
        DrawCircle(&circle2);
    }

    // const_cast
    // - removes constness
    // - use with caution in multithreaded code
    void ConstCast()
    {
        // TODO
    }

    // reinterpret_cast is used to cast:
    // - pointer-to-type to unrelated pointer-to-type	
    // - reference-to-type to unrelated reference-to-type
    // - pointer-to-function to pointer-to-function
    void ReinterpretCast()
    {
        // TODO
    }
}
