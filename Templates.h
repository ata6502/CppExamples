#pragma once

#include <iostream>
#include <iomanip> // setiosflags, setprecision
#include <tuple> // pair, tuple, get
#include <string>
#include <complex>

using std::cout;
using std::endl;
using std::string;

/*
    In C++ the template arguments don't have to be type names. 
    They can be variable names, function names, and constant 
    expressions as well.

    Variadic templates allow templates to take an arbitrary 
    number of type parameters.

    Local and unnamed types can be used as template arguments.

     T::value_type returns:
    - int if T is vector<int>
    - string if T is vector<string>
    - Resource if T is vector<Resource> etc.
    It's an implied constraint. It's up to the programmer to pass the correct type as T. 
    In the following example, T has to have the value_type member which ctor has to accept 
    a string. For example, std::string has the value_type member and it can be constructed 
    from a string.
    T::value_type res("entry");
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
    namespace VariadicTemplates
    {
        // Specialization in case when there is only one argument .
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

        void Test()
        {
            cout << std::setprecision(1) << adder(1, 2.2, 3, 4) << " ";
            cout << adder(string("a"), string("b"), string("c")) << " ";
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


    void Templates()
    {
        ConsumingTemplates::Test();
        TemplateClasses::Test();
        TemplateFunctions::Test();
        TemplateSpecialization::Test();
        VariadicTemplates::Test();
    }
}