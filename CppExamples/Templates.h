#pragma once

#include <iostream>
#include <iomanip> // setiosflags, setprecision
#include <tuple> // pair, tuple, get
#include <string>
#include <complex>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::tuple;
using std::vector;

/*
    Template arguments:
    - don't have to be type names
    - can be variable names, function names, and constant expressions
    - local and unnamed types can be used as template arguments

    Variadic templates (C++11):
    - allow templates to take an arbitrary number of type arguments
    - perform type computation at compile-time (template meta-programming)
    - an example of a variadic template function: std::make_unique
    - an example of a variadic template class: std::tuple

    Template aliases (C++11):
    - similar to typedefs with partially bound template arguments

    T::value_type returns:
    - int if T is vector<int>
    - string if T is vector<string>
    - Resource if T is vector<Resource> etc.
    It's an implied constraint. It's up to the programmer to pass the correct type as T. 
    In the following example, T has to have the value_type member which ctor has to accept 
    a string. For example, std::string has the value_type member and it can be constructed 
    from a string.
    T::value_type res("entry");

    Default values for function template parameters:
    Default numerical value: template <typename T, int N=1> T& increment(T& i)
    Default type value: template <typenameT, typename C = std::less<T>>T FindExtreme(std::vector<T> &v, C c = C())
*/
namespace TemplatesExamples
{
    //
    // Consuming Templates
    //
    namespace ConsumingTemplates
    {
        typedef std::pair<int, int> IntPair;
        typedef std::tuple<int, int, int> Trie; // tuple is a variadic template



        // Return a pair of values: a sum and a product.
        IntPair SumAndProduct(int a, int b)
        {
            return IntPair(a + b, a*b);
        }

        Trie SumProductAverage(int a, int b, int c)
        {
            Trie t{ a + b + c, a*b*c, (a + b + c) / 3 };
            return t;
        }

        void Tuples()
        {
            // std::tuple has built-in comparison operators that check whether two tuples are the same or not.

            // Create tuples using uniform initialization.
            tuple<int, string, double> entry1{ 1, "A", 11.1 };
            tuple<int, string, double> entry2{}; // use default values for each element: 0, "", 0.0

            // Create tuples using make_tuple.
            auto entry3 = std::make_tuple(1, "A", 22.0);

            vector<std::tuple<int, std::string, double>> vec
            { 
                std::make_tuple(2, "B", 22.2),
                std::make_tuple(3, "C", 33.3),
                std::make_tuple(4, "D", 44.4) 
            };

            // Get the value out of a tuple and/or change it using the template function get<T>()
            // that takes a tuple instance. The type parameter is a 0-based index of a tuple element
            // we want to get. The get function returns a reference to the tuple element.
            std::get<2>(entry1) = 88.8; // 0 is int, 1 is string, 2 is double

            // Insert a tuple at the beginning of a vector.
            vec.insert(begin(vec), entry1);

            // Iterate over our vector of tuples.
            for (const auto& v : vec)
            {
                std::cout << std::get<1>(v);
            }

            cout << " ";
        }

        void Test()
        {
            int a = 2, b = 3;
            auto r1 = SumAndProduct(a, b);
            cout << "Sum:" << r1.first << ",Prod:" << r1.second << " ";
            cout << "Sum:" << std::get<0>(r1) << ",Prod:" << std::get<1>(r1) << " "; // equivalent to r1.first and r1.second

            int c = 4;
            auto r2 = SumProductAverage(a, b, c);
            cout
                << "Sum:" << std::get<0>(r2)
                << ",Prod:" << std::get<1>(r2)
                << ",Avg:" << std::get<2>(r2) << " ";

            Tuples();
        }
    }


    //
    // Template Classes
    //
    namespace TemplateClasses
    {
        // Our custom Tuple class.
        template<typename T1, typename T2, typename T3>
        struct Triple // it could be 'class' instead of 'struct'
        {
            T1 first;
            T2 second;
            T3 third;

            Triple(const T1& first, const T2& second, const T3& third)
                : first(first), second(second), third(third) { }
        };

        typedef Triple<int, int, int> Trie;

        Trie SumProductAverage(int a, int b, int c)
        {
            // ??? Although our Triple template does not support uniform initialization
            // we are using it here and it's fine. Why? Without uniform initialization
            // we would need to use the ctor.
            Trie t{ a + b + c, a*b*c, (a + b + c) / 3 };
            return t;
        }

        // An Acumulator template class.
        template <class T>
        class Accumulator
        {
        public:
            Accumulator(T start) : m_total(start) { };
            T operator+=(const T& t) { return m_total += t; };
            T GetTotal() { return m_total; }
        private:
            T m_total;
        };

        void Test()
        {
            //
            // SumProductAverage
            //
            auto res = SumProductAverage(2, 3, 4);
            cout
                << "Sum:" << res.first
                << ",Prod:" << res.second
                << ",Avg:" << res.third << " ";

            //
            // Accumulator
            //
            Accumulator<int> accum(0); // always specify a type for class templates
            accum += 3;
            accum += 7;
            cout << accum.GetTotal() << " ";

            Accumulator<string> accum2("");
            accum2 += "Hello";
            accum2 += "World";
            cout << accum2.GetTotal() << " ";
        }
    }


    //
    // Template Functions
    //
    namespace TemplateFunctions
    {
        template<typename T1, typename T2, typename T3>
        struct Triple
        {
            T1 first;
            T2 second;
            T3 third;

            Triple(const T1& first, const T2& second, const T3& third)
                : first(first), second(second), third(third) { }
        };

        template<typename T1, typename T2, typename T3>
        Triple<T1, T2, T3> SumProductAverage(const T1& a, const T2& b, const T3& c)
        {
            return Triple<T1, T2, T3>(a + b + c, a*b*c, (a + b + c) / 3);
        }

        template<typename T>
        T Min(const T& a, const T& b)
        {
            return (a < b ? a : b);
        }

        template<typename T>
        T Max(const T& a, const T& b)
        {
            return (a > b ? a : b);
        }

        template<typename T>
        void Print(T a[], unsigned int size)
        {
            for (unsigned int i = 0; i < size; ++i)
                cout << a[i];
        }

        template<typename T>
        void WriteColumn(const T& val, const string& terminator)
        {
            // If T and U name the same type (including const/volatile qualifications), 
            // std::is_same provides the member constant value equal to true. Otherwise 
            // value is false.
            if (std::is_same<typename std::remove_const<T>::type, string>::value)
                cout << "1 ";
            else
                cout << "2 ";
        }

        void Test()
        {
            //
            // SumProductAverage
            //
            int a = 14;
            double b = 5.0;
            float c = -3.5f;

            auto res = SumProductAverage(a, b, c);
            cout
                << "Sum:" << res.first
                << ",Prod:" << std::setiosflags(std::ios::fixed) << std::setprecision(3) << res.second
                << ",Avg:" << std::setiosflags(std::ios::fixed) << std::setprecision(3) << res.third << " ";

            //
            // MinMax test
            //
            int p = 2, q = 8;
            cout << "min:" << Min(p, q) << " "; // the compiler figures out what type you want to use; the same as Min<double>(a,b)
            cout << "max:" << Max(p, q) << " ";

            char x = 'e', y = 'c';
            cout << "min:" << Min(x, y) << " ";
            cout << "max:" << Max(x, y) << " ";

            double f1 = 3.4, f2 = 2.6;
            cout << "min:" << std::setiosflags(std::ios::fixed) << std::setprecision(3) << Min(f1, f2) << " ";
            cout << "max:" << std::setiosflags(std::ios::fixed) << std::setprecision(3) << Max(f1, f2) << " ";

            // Declare explicitly that you want to return a double.
            double f3 = Max<double>(33, 2.0);
        }
    }


    //
    // Template Specialization
    //
    // Used to tell the compiler to generate a template for a particular type.
    // It may be useful when the type does not implement certain operations
    // such as > or + which are used in the template.
    // The first choice is to add a missing operator or a function. If you
    // do not own the code you can extend the type by creating a free function
    // for the operator.
    // The second choice is to specialize the template.
    namespace TemplateSpecialization
    {
        // Specializes a template for a particular type.
        // As an example, we specialize the complex type.

        template<typename T1, typename T2, typename T3>
        struct Triple
        {
            // Project T1 as the result type. It's not a good practice.
            // It's better to specify an explicit return type.
            typedef T1 ResultType;

            T1 first;
            T2 second;
            T3 third;

            Triple(const T1& first, const T2& second, const T3& third)
                : first(first), second(second), third(third) { }
        };

        template<typename T1, typename T2, typename T3>
        Triple<T1, T2, T3> SumProductAverage(const T1& a, const T2& b, const T3& c)
        {
            return Triple<T1, T2, T3>(a + b + c, a * b * c, 
                (a + b + c) / Triple<T1, T2, T3>::ResultType(3)); // treats 3 as the ResultType which is projected to T1 in Triple which in turn is complex
        }

        typedef std::complex<double> ComplexDouble;
        typedef Triple<ComplexDouble, ComplexDouble, ComplexDouble> TripleComplexDouble;

        // We want perform calculations only on the real part of the complex arguments.
        // To achieve that we define a special implementation of the function SumProductAverage
        // that works only for complex numbers of type double.
        template<> TripleComplexDouble SumProductAverage(const ComplexDouble& a, const ComplexDouble& b, const ComplexDouble& c)
        {
            auto res = SumProductAverage(a.real(), b.real(), c.real());
            return TripleComplexDouble(res.first, res.second, res.third);
        }

        // Accumulator template
        template <class T>
        class Accumulator
        {
        public:
            Accumulator(T start) : m_total(start) { };
            T operator+=(const T& t) { return m_total += t; };
            T GetTotal() { return m_total; }
        private:
            T m_total;
        };

        struct Book
        {
            string Title;
            float Price;
        };

        // Accumulator specialization: tells the compiler how to accumulate books.
        template <>
        class Accumulator<Book>
        {
        public:
            Accumulator(float start) : m_total(start) { };
            float operator+=(const Book& b) { return m_total += b.Price; };
            float GetTotal() { return m_total; }
        private:
            float m_total;
        };

        void Test()
        {
            ComplexDouble a(2, 3), b(3, 4), c(4, 5);

            // Call the specialized implementation of SumProductAverage.
            auto res = SumProductAverage(a, b, c);
            cout << std::setprecision(0)
                << "Sum:" << res.first
                << ",Prod:" << res.second
                << ",Avg:" << res.third << " ";

            Book b1{ "A", 8.0f };
            Book b2{ "B", 0.8f };

            Accumulator<Book> accum(0.0f);
            accum += b1;
            accum += b2;
            cout << std::setprecision(1) << accum.GetTotal() << " ";
        }
    }


    //
    // Variadic Templates
    //
    /*
    // variadic class template
    template <typename... Ts>
    class Foo { };

    // variadic function template
    template <typename... Ts>
    void foo(Ts... vals){ }

    // an example of a variadic template (simplified)
    template<class _T, class... _Types> inline
    unique_ptr<_T> make_unique(_Types&&... _Args)
    {
        // Construct _T forwarding the parameter pack to the _T's constructor.
        return (unique_ptr<_T>(new _T(std::forward<_Types>(_Args)...)));
    }

    The construct Ts... vals is called a parameter pack.
    You can do the following with the parameter pack:
    - expand it with the expansion operator ...
    - pass it to another template or a function
    - use it in an initializer list
    - capture it with a lambda
    - get the number of type parameters using sizeof...(T)
    The paramter pack has to appear as the last on the parameter list.

    Two approaches to writing a template function or a member function of a templated class:
    - forwarding - forward the parameter pack to another function e.g., make_share takes parameters and forwards them to a ctor of the object being constructed
    - recursive templates - involves writing several templates with the same name that take different number of arguments; 
                            the compiler starts chooses the appropriate template;
                            if there is no template with the appropriate number of arguments, the compiler chooses the variadic template

    Expansion rules: 
    - echo is a function that takes type parameters Ts with values vs
    - b is a member function of a class A
    echo(A<Ts...>::b(vs...));   // in b(vs...), vs are passed as a parameter pack to b i.e., b is called once
    echo(A<Ts...>::b(vs)...);   // calls b as many times as there are parameters in the parameter pack; example: pass A<int,int> for the 1st value in the parameter pack, pass A<int,int> for the 2nd value in the parameter pack
    echo(A<Ts>::b(vs)...);      // Ts and vs are expanded in parallel: b is called with the first type in Ts and the first value in vs, etc.; it expands the combination of Ts and vs
    */
    namespace VariadicTemplates
    {
        // Specialization in case when there is only one argument.
        template<typename T>
        T adder(T v)
        {
            return v; // just return the argument
        }

        // Calculate the sum of any number of values.
        template<typename T, typename... Args>
        T adder(T first, Args... args) // PRB: the return type is the type of the first argument
        //auto adder(T first, Args... args) -> decltype(first + adder(args...)) // the return type is the sum of the first argument and the other arguments, PRB: compiler error
        {
            return first + adder(args...); // when there are at least two arguments
        }

        // An example of a recursive variadic template. It uses different versions of the template that 
        // takes less parameters, until it works its way down to the non-variadic template that just takes 
        // the two parameters. 

        // A non-variadic function template. It takes rvalues as parameters in order to avoid copying
        // or forcing the user to create a temporary object just to pass it as a reference.
        template <class T, class U>
        bool matches(T&& t, U&& u)
        {
            return t == u;
        }

        // A variadic version of the above function template. It takes at least two parameters T and U.
        template <class T, class U, class... Ts>
        bool matches(T&& t, U&& u, Ts&&... vals)
        {
            // Compare the first parameter with all other parameters one-by-one recursively.
            // It calls the variadic or non-variadic version depending on the number of parameters
            // still left to match.
            return t == u || matches(t, vals...);
        }

        void VariadicTemplate()
        {
            cout << std::setprecision(1) << adder(1, 2.2, 3, 4) << " ";     // 10 (not 10.2 because the type returned by adder is the same as the type of the first argument)
            cout << adder(string("a"), string("b"), string("c")) << " ";    // abc
        }

        //
        // Recursive variadic template
        //
        void RecursiveVariadicTemplate()
        {
            // Use the non-variadic function template.
            bool p = matches(1, 2);         // false
            bool q = matches(1, 2 - 1);     // true

            // Use the variadic function template.

            // #1: t=1 u=2 vals={1}
            // #2: t=1 u=1 (non-variadic)
            bool a = matches(1, 2, 1);      // true

            // #1: t=1 u=2 vals={3,4,5}
            // #2: t=1 u=3 vals={4,5}
            // #3: t=1 u=4 vals={5}
            // #4: t=1 u=5 (non-variadic)
            bool b = matches(1, 2, 3, 4, 5); // false

            std::string x{ "A" };
            std::string y{ "B" };
            std::string z{ "A" };
            bool t = matches(x,y,z); // true

            // 'true' is promoted to an integer. The compiler shows a warning about
            // mixing int and bool.
            bool mixing = matches(1, 2.2, 3.3, true); // true
        }

        //
        // Expansion rules - the placement of ... matters
        //

        // The function template echo takes some Ts called vs.
        template <class... Ts> 
        void e(Ts... vs)
        {
            // Determine and display the number of elements passed.
            int cnt = sizeof... (Ts);
            cout << "e:cnt=" << cnt << ",";

            // Declare a vector of integers and pass vs as an initializer list.
            vector<int> values{ vs... };
        }

        // The class template A works with types Ts.
        template<class... Ts>
        class A
        {
        public:
            // The function b takes a package of Ts. We call the package vs for values.
            // b is going to be called repeatedly.
            static int b(Ts... vs)
            {
                // Determine and display the number of parameters passed.
                int cnt = sizeof... (Ts);
                cout << "b:cnt=" << cnt << ",";

                // Return the number of parameters.
                return cnt;
            }
        };

        template <class... Ts> void DotTest(Ts... vs)
        {
            // b called once with 3 parameters.
            // e called once with a single parameter - the value 3 returned from b.
            // b:cnt=3,e:cnt=1
            e(A<Ts...>::b(vs...));

            cout << " ";

            // First, b is called 3 times each with a single parameter.
            // Next, e is called once with three parameters - the values {1,1,1} returned from b.
            // b:cnt=1,b:cnt=1,b:cnt=1,e:cnt=3
            e(A<Ts>::b(vs)...);
        }

        template <class... Ts> void DotTest2(Ts... vs)
        {
            // Ts are not expanded.
            // vs are expanded.
            // b called three times, each with one v.
            // First, A is materialized with 3 parameters. Next, b is called multiple times, each with one of the parameters at a time. 
            e(A<Ts...>::b(vs)...);
        }

        void ExpansionRules()
        {
            DotTest(8, 'A', true);
            cout << " ";

            // e(A<Ts...>::b(vs...));   b:cnt=0,e:cnt=1
            // e(A<Ts>::b(vs)...);      e:cnt=0
            DotTest();

            // b is not prepared to accept parameters passed to A which are <int,char,bool>
            // Error C2672: 'TemplatesExamples::VariadicTemplates::e': no matching overloaded function found
            // Error C2660: 'TemplatesExamples::VariadicTemplates::A<int,char,bool>::b': function does not take 1 arguments
            //DotTest2(9, 'B', false);
        }

        void Test()
        {
            VariadicTemplate();
            RecursiveVariadicTemplate();
            ExpansionRules();
        }
    }

    //
    // Template Metaprogramming
    //
    namespace TemplateMetaprogramming
    {
        // Calculate factorial.

        template <int n> struct Factorial
        {
            enum { value = n * Factorial<n - 1>::value };
        };

        // Stopping condition for the recursion.
        template <> struct Factorial<0>
        {
            enum { value = 1 };
        };

        void Test()
        {
            // Pre-calculate factorials in *compile time*.
            int x = Factorial<4>::value; // 24
            int y = Factorial<0>::value; // 1
        }
    }

    //
    // Default values for function template parameters
    //
    namespace DefaultTemplateParameters
    {
        // so here I'm saying I'd like to use standard greater instead of standard less, and I have to also tell it that this will be working with a vector of integers, and that will bring me the minimum. So, let's take a look, it thinks the minimum is 4, and if we take a look at nums, that's true, the minimum is 4. These are not hard templates to write, and enabling there to be a default value actually makes these much easier to use. An increment function that you had to every time say, oh by the way this is an integer, and by the way I'd like to increment it by 1, I don't think you would ever use. And to find Extreme Function that you had to specify the type and the comparer every time, again I don't think you would use. So being able to have defaults makes these templates easier to write, and also easier to use. 

        // The function template Increment works with any type that 
        // has the += operation.
        template <typename T, int N = 1> T& Increment(T& i)
        {
            i += N; return i;
        }

        // The second type parameter is a comparer, which by default is the std::less comparer.
        // The second parameter for the function template FindExtreme c=C() is an instance of the comparer.
        template <typename T, typename C = std::less<T> >
        T FindExtreme(std::vector<T>& v, C c = C())
        {
            // We dereference an iterator returned from std::max_element.
            // The value returned is of type T.
            return *std::max_element(begin(v), end(v), c); // c is the comparer
        }

        void Test()
        {
            std::vector<int> nums{ 6, 2, 3, 4, 5, 1 };

            // Use the default value of 1 for the Increment's second argument.
            // The compiler figures out that it needs to generate a template for int.
            for (int& i : nums)
                i = Increment(i); // nums = {7,3,4,5,6,2}

            // Provide the value of 2 for the Increment's second argument.
            // This time we need to specify the template type explicitly.
            for (int& i : nums)
                i = Increment<int, 2>(i); // nums = {9,5,6,7,8,4}

            // Find the extreme using the std::less comparer.
            // This finds the maximum.
            int max = FindExtreme(nums); // 9

            // Find the extreme using the std::greater comparer.
            // This finds the minimum.
            int min = FindExtreme<int, std::greater<int>>(nums); // 4
        }
    }


    void Templates()
    {
        ConsumingTemplates::Test();
        TemplateClasses::Test();
        TemplateFunctions::Test();
        TemplateSpecialization::Test();
        VariadicTemplates::Test();
        DefaultTemplateParameters::Test();
    }
}