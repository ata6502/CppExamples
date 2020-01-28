#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <random> // mt19937, normal_distribution

using std::cout;
using std::endl;
using std::string;

/*
    rand() - generates an integer between 0 and RAND_MAX
    rand() % n - generates an integer in the range 0 to n-1 (scaling); n is the scaling factor
    a + rand() % b
        a is the shifting value (the first number in the desired range)
        b is the scaling factor (the width of the desired range)
    a + rand() % (b - a + 1)
        a <= n <= b
*/

namespace RandExamples
{
    void RandomNumbers()
    {
        int n;

        for (int i = 1; i <= 10; ++i)
        {
            n = rand() % 2;         // 0 or 1
            cout << n;
        }
        cout << " ";

        for (int i = 1; i <= 10; ++i)
        {
            n = 1 + rand() % 2;     // 1 or 2
            cout << n;
        }
        cout << " ";

        for (int i = 1; i <= 10; ++i)
        {
            n = rand() % 10;        // 0 <= n <= 9; the width of the desired range is 10: 0,1,2,3,4,5,6,7,8,9
            cout << n;
        }
        cout << " ";

        for (int i = 1; i <= 10; ++i)
        {
            n = 1 + rand() % 100;   // 1 <= n <= 100
            cout << n << ",";
        }
        cout << " ";

        for (int i = 1; i <= 10; ++i)
        {
            n = 4 + rand() % 7;     // 4 <= n <= 10    10 - 4 + 1 = 7
            cout << n;
        }
        cout << " ";

        for (int i = 1; i <= 10; ++i)
        {
            n = -1 + rand() % 3;    // -1 <= n <= 1    1 - (-1) + 1 = 3
            cout << n << ",";
        }
        cout << " ";

        for (int i = 1; i <= 10; ++i)
        {
            n = -3 + rand() % 15;   // -3 <= n <= 11   (11 - (-3) + 1) = 15
            cout << n << ",";
        }
        cout << " ";
    }

    // RandFloat generates a random float number in the rage (min,max).
    float RandFloat(float min, float max)
    {
        return (static_cast<float>(rand() % RAND_MAX) / static_cast<float>(RAND_MAX)) * (max - min) + min;
    }

    void TestRandFloat()
    {
        float f;
        float min = 10.f, max = 0.f;

        for (int i = 1; i <= 2000; ++i)
        {
            f = RandFloat(2.f, 5.f);   // 2.0 <= f <= 5.0
            if (f < min) min = f;
            if (f > max) max = f;
        }

        cout << std::setprecision(10) << "min=" << min << " ";
        cout << std::setprecision(10) << "max=" << max << " ";
    }

    void StrongRandomization()
    {
        // available in C++ 11+
        auto seed = std::chrono::system_clock::now()
            .time_since_epoch().count();
        std::mt19937 gen(seed); // Mersenne twister
        std::normal_distribution<float> nd; // normal distribution with the mean 0 and the variance 1

        cout << "Mersenne twister: ";
        for (size_t i = 1; i < 10; ++i)
            cout << std::setprecision(2) << nd(gen) << ",";
    }

    void Test()
    {
        // Start the random generator. It needs to be done once per program run.
        srand((unsigned)time(nullptr));

        RandomNumbers();
        TestRandFloat();
        StrongRandomization();
    }
}