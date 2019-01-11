#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional> // std::function

using std::cout;
using std::endl;
using std::vector;
using std::string;

/*
    Lambda expressions allow you to write anonymous functions inline, removing the need to write
    a separate function or to write a function object.

    Use an explicit capture block for lambda expressions:
    - Avoid using [&] and [=].
    - By default, captured variables are const.
    - Examples:
        []     - captures nothing (no variables from the enclosing scope are captured)
        [i]    - captures i by value (makes a copy of i)
        [&j]   - captures j by reference (changes are reflected in the actual variable; dangling reference may be an issue (?)
        [=]    - captures all variables needed by lambda by value (copies the variables)
        [&]    - captures all variables needed by lambda by reference
        [=, &x, &y] - captures by value by default, except variables x and y, which are captured by reference
        [&, x] - captures by reference by default, except variable x, which is captured by value
        [&x, &x] - illegal because identifiers cannot be repeated

    Syntax:
    [](){}
    [capture_clause](parameters) mutable exception_specification -> return_type { body }
    capture_clause: [capture_default capture_list]

    std::function is commonly used with lambda. It's similar to C#'s Func and Action delegate.
    Example: A wrapper for a function that returns a double and takes two integers as parameters:
    function<double(int, int)> wrapper;
*/

namespace LambdaExamples
{
    void LambdaInvocation()
    {
        //
        // Create a lambda expression and immediately execute it.
        //

        // Simple lambda.
        vector<int> v = { 1, 2, 3 };
        std::for_each(v.begin(), v.end(),
            [](int i) { cout << i; });
        cout << " ";

        // Define a lambda expression without return type and without any parameters. 
        // Note the parentheses () at the end, which cause the lambda to execute immediately.
        [] { cout << "Hello "; }();

        // Define a lambda that accepts a string argument and returns a string. Store the result
        // in the variable 'result'. The return type can be omitted in this case.
        // Notice the parentheses at the end of the lambda causing the lambda to be executed immediately.
        string result = [](const string& s) -> string { return s; }("Aye!");
        cout << result << " ";

        // Store a pointer to a lambda expression and execute the lambda through the function pointer. 
        auto fn = [](const string& s) { return s; };
        cout << fn("Call1 ");
        cout << fn("Call2 ");
    }

    void ExplicitReturnType()
    {
        vector<int> v = { 1, 2, 3, 4 };
        vector<double> dv;

        // Specify the return type explicitly. We need to specify the return type
        // because this lambda has multiple returns.
        std::transform(v.begin(), v.end(), std::back_inserter(dv),
            [](int n) -> double
        {
            if (n % 2 == 0)
                return n * n * n;
            else
                return n / 2.0;
        });

        // Output: 0.5 8 1.5 64
        for (double d : dv)
            cout << d << " ";

        // Another similar example.
        [](int i) -> double
        {
            if (i > 10)
                return 0.0;
            return double(i);
        };
    }

    /*
        If variables from the enclosing scope are captured by value, a copy of those variables will become available
        in the body of the lambda expression. Those copies are const by default. If the lambda expression is marked 
        as mutable, the copies are not const and the lambda body can modify the local copies.
    */
    void MutableLambda()
    {
        vector<int> v = { 1, 2, 3, 4 };

        int x = 1;
        int y = 1;

        // Capture variables x and y by value by specifying [=]. 
        // Inside the lambda, we have local copies of x and y.
        // Specify 'mutable' to remove constness from the variables x and y.
        // The variable r (the vector's element) is passed by reference.
        std::for_each(v.begin(), v.end(), [=](int& r) mutable
        {
            const int old = r;

            // Change the real value of the vector's element because it is passed by ref.
            r *= 2;

            // 'mutable' allows the following lines to compile. Normally, variables captured
            // by values (here x and y) are const but here we have local copies of x and y.
            x = y;
            y = old;

            r += x + y;
        });

        // Output: 4 7 11 15
        // Keep in mind that the variables x and y are captured in lambda.
        for (double d : v)
            cout << d << " ";
    }

    std::function<int(void)> ReturnLambda(int x)
    {
        // int(void) is a function accepting no arguments and returning an integer.
        return [x]()->int {return 2 * x; }; // the same as return [x]{return 2*x;};
    }

    void SetLambda(const std::function<bool(double)>& lambda)
    {
        // store the lambda in a variable of type function<bool(double)>
    }

    void ReturnAndSetLambda()
    {
        // Create a lambda expression of type std::function<int(void)>
        auto multiplier = ReturnLambda(3);
        cout << multiplier() << " "; // 6

        // Pass a lambda as a param.
        SetLambda([](double d) { return d > 0.0; });
    }

    void Lambda()
    {
        LambdaInvocation();
        ExplicitReturnType();
        MutableLambda();
        ReturnAndSetLambda();
    }
}