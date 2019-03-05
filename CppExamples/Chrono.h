#pragma once

#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

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

    void Test()
    {
        auto const start = TimeNow();

        for (unsigned long i = 0; i < 100 * 1000000; ++i)
        {
            auto a = 0;
            a = a * 10;
        }

        cout << "Seconds:" << TimeElapsed(start) << " ";
    }
}
