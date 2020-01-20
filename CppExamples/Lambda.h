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
    - Avoid using [&] and [=]. Specify explicitly what variables you capture.
    - When you use [&] or [=] only variables used in lambda are captured.
    - By default, captured variables are const.
    - Default capture modes implicitly capture 'this'. You can only access class members by capturing 'this'

    Examples:
        []     - captures nothing (no variables from the enclosing scope are captured)
        [i]    - captures i by value (makes a copy of i)
        [&j]   - captures j by reference (changes are reflected in the actual variable; dangling reference may be an issue when the original variable j goes out of scope
        [=]    - captures all variables that are needed in lambda by value (copies the variables)
        [&]    - captures all variables that are needed in lambda by reference
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

    By default, the captured variables are const. Use the mutable keyword if you need to modify the variables:
    - If a variable is captured by value, the local copy will be changed.
    - If a variable is captured by reference, the referenced variable will be changed.

    default capture modes implicitly captures *this* and you can only access class members by capturing *this*
*/

namespace LambdaExamples
{
    void BasicLambda()
    {
        // Store a lambda in a variable.
        auto doubleValue = [](int z) { return z * 2; };
        cout << doubleValue(4) << " "; // 8

        // Store a lambda in std::function
        std::function<bool(double)> isGreaterThanZero = [](double d) { return d > 0.0; };
        cout << isGreaterThanZero(1.0) << " "; // true

        // A lambda in a for_each loop.
        vector<int> v = { 1, 2, 3 };
        std::for_each(v.begin(), v.end(),
            [](int i) { cout << i; }); // lambda is handed each element of the vector: 1,2,3
        cout << " ";
    }

    void GenericLambda()
    {
        vector<int> v = { 1, 2, 3 };

        // Generic lambdas accept auto parameters.
        auto doubleValueGeneric = [](auto z) { return z * 3; };
        cout << doubleValueGeneric(2) << " "; // 6

        // Generic lambdas are especially useful with other functions when we don't know the exact type of arguments.
        int oddsCount = std::count_if(begin(v), end(v), [](auto n) { return n % 2 != 0; });
        cout << oddsCount << " "; // 2

        // Another example of a generic lambda.
        auto cat = [](auto x, auto y) { return x + y; };
        cout << cat(1, 2) << " "; // 3
        cout << cat(string("a"), string("b")) << " "; // ab

        // Displaying values of different types.
        auto printLine = [](auto item) {cout << item << " "; };
        printLine(8);
        printLine("qq");
    }

    void CaptureVariables()
    {
        // Capture a variable by value.
        int x = 4;
        auto increaseValue = [x](int z) { return z + x; };
        cout << increaseValue(3) << " "; // 7
        x = 10; // change the variable
        cout << increaseValue(3) << " "; // still 7 because the variables are captured by value and x was 4 when it was captured: 3 + 4 = 7
    }

    void SpecifyReturnType()
    {
        vector<int> v = { 1, 2, 3, 4 };
        vector<double> dv;

        // Specify the return type explicitly. We need to specify the return type
        // because this lambda has multiple returns.
        // std::transform transforms a collection into another collection.
        // std::back_inserter inserts transfomed items at the back of a collection. 
        // To insert transfomed items at the beginning of the collection, use begin(dv) instead.
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

    // If the lambda expression is marked as mutable, the copies of captured 
    // variables are not const and the lambda body can modify the local copies.
    void MakeLambdaMutable()
    {
        vector<int> v = { 1, 2, 3, 4 };

        int x = 1;
        int y = 1;

        // Capture variables x and y by value by specifying [=]. 
        // Inside the lambda, we have local copies of x and y.
        // Specify 'mutable' to remove constness from the variables x and y.
        // The variable r (the vector's element 1,2,3,4) is passed by reference.
        std::for_each(v.begin(), v.end(), [=](int& r) mutable
        {
            const int old = r;

            // Change the real value of the vector's element because it is passed by ref.
            r *= 2;

            // 'mutable' allows the following lines to compile. Normally, variables captured
            // by values (here x and y) are const but here the local copies of x and y are mutable.
            x = y;
            y = old;

            r += x + y;
        });

        // Output: 4 7 11 15
        for (double d : v)
            cout << d << " ";

        // x and y are unchanged because lambda modified copies of x and y.
        cout << x << " " << y << " ";

        // Output: 012
        vector<int> vec1;
        int n = 0;
        std::generate_n(std::back_inserter(vec1), 3, [n]() mutable { return n++; });
        for (auto i : vec1)
            cout << i;
        cout << "-" << n << " ";

        // The same output: 012
        vector<int> vec2;
        n = 0;
        std::generate_n(std::back_inserter(vec2), 3, [&n] { return n++; });
        for (auto i : vec2)
            cout << i;
        cout << "-" << n << " ";
    }

    // Non-local variables can always be accessed in a lambda.
    std::function<bool()> AccessNonLocalVariables()
    {
        static auto a = 5;
        static auto b = -3;
        return []() { return a + b > 0; };
    }

    void ExecuteImmediately()
    {
        // The parentheses () at the end of a lambda cause the lambda to execute immediately.
        // This pattern is called Immediately Invoked Lambda Expression (IILE).

        // Define a lambda without return type and without any parameters. 
        [] { cout << "A "; }();

        // Define a lambda that accepts a string argument and returns a string. 
        // The return type can be omitted in this case.
        string result = [](const string& s) -> string { return s; }("Aye!");
        cout << result << " ";

        // You can assign a lambda that executes immediately to a const.
        int const a = [=]() { return 8; }();
        cout << a << " ";
    }

    void ConvertToFunctionPointer()
    {
        // Convert a lambda to a function pointer.
        typedef int(*Func)();
        Func f = [] { return 10; };
        f(); // invoke lambda via function pointer
    }

    struct Order { int Number; };
    struct Customer { string Name; vector<Order> Orders; };

    void LambdaNesting()
    {
        vector<Customer> customers;
        customers.push_back(Customer{ "A", { {1},{2} } });
        customers.push_back(Customer{ "B", { {3},{4} } });
        customers.push_back(Customer{ "C", { {5},{6} } });

        for_each(begin(customers), end(customers),
            [=](const Customer& c)
        {
            cout << c.Name << ":";

            for_each(begin(c.Orders), end(c.Orders), 
                [=](const Order& o)
            {
                cout << o.Number;
            });

            cout << " ";
        });
    }

    void EmulateRecursion()
    {
        // recursion emulation via std::function
        std::function<int(int)> fibonacci = [&](int n) -> int
        {
            if (n < 1)
                return -1;
            else if (n == 1 || n == 2)
                return 1;
            else
                return fibonacci(n - 1) + fibonacci(n - 2);
        };

        cout << "Fib(7)=" << fibonacci(7) << " ";
    }

    void UndefinedBehaviour()
    {
        {
            std::function<int()> f;
            {
                auto i = 5;
                f = [&i] { return i; }; // i is caught by reference
            }
            auto i = 10;
            f(); // undefined because i is out of scope
        }

        {
            std::function<int()> f;
            {
                auto p = new int(10);
                f = [=] { return *p; };
                delete p;
            }
            f(); // undefined behavior because p has been deleted
        }
    }

    void CaptureByMove()
    {
        auto p1 = std::make_unique<string>("a");

        // ...

        // Hand the unique_pointer somewhere else forever.
        // We expect item to be a pointer so we could dereference it.
        auto printLine = [](auto item) { cout << *item << " "; };

        // We need to move the unique_pointer rather than copy it because
        // unique_pointers do not support copying. After the move, the p1 
        // pointer is empty.
        printLine(std::move(p1));

        // Another unique pointer.
        auto p2 = std::make_unique<string>("b");

        // Capture a pointer by move. Also, alias it as 'item'.
        auto printLineWithMove = [item = std::move(p2)]() { cout << *item << " "; };
        printLineWithMove();
    }

    void Test()
    {
        BasicLambda();
        GenericLambda();
        CaptureVariables();
        SpecifyReturnType();
        ReturnAndSetLambda();
        MakeLambdaMutable();
        AccessNonLocalVariables()(); // AccessNonLocalVariables returns a lambda; the second parentheses cause the lambda to execute immediately
        ExecuteImmediately();
        ConvertToFunctionPointer();
        LambdaNesting();
        EmulateRecursion();
        UndefinedBehaviour();
        CaptureByMove();
    }
}