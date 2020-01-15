#pragma once

#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

/*
    The chrono library provides a selection of clocks with different tick rates.
*/
namespace ChronoExamples
{
    high_resolution_clock::time_point TimeNow()
    {
        // Return the current value of the clock.
        return high_resolution_clock::now();
    }

    float TimeElapsed(high_resolution_clock::time_point const & start)
    {
        // Calculate the duration in ticks and cast it to fractions of a second
        // using the duration_cast.
        return duration_cast<duration<float>>(TimeNow() - start).count();
    }

    // Calculates the Fibonacci number using the very slow recursive approach.
    long SlowFunction(unsigned n)
    {
        if (n < 2)
            return n;

        return SlowFunction(n - 2) * SlowFunction(n - 1);
    }

    // Measures running time in milliseconds of the function passed as the parameter.
    // The parameter f has to support the round brackets ().
    template <typename Func>
    long long TimeElapsedFunc(Func f)
    {
        auto begin = steady_clock::now();
        f();
        auto end = steady_clock::now();

        return duration_cast<milliseconds>(end - begin).count();
    }

    void Test()
    {
        auto const start = TimeNow();
        SlowFunction(30);
        cout << "TimeElapsed:" << TimeElapsed(start) << " ";

        auto time = TimeElapsedFunc([&]() { SlowFunction(30); });
        cout << "TimeElapsedFunc[ms]:" << time << " ";
    }
}
