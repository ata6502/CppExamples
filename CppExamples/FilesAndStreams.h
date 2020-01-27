#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // sort, unique_copy
#include <iomanip> // setprecision
#include <fstream> // ofstream, ifstream
#include <sstream> // ostringstream

using std::cout;
using std::endl;
using std::string;
using std::vector;

using std::ifstream;
using std::ofstream;

/*
    - The stream insertion operation (<<) is used for concatenating (also called 'chaining' or 'cascading') the input streams.
    - Streams are not copyable; they should be passed by reference, for example: void AddToBuffer(const std::wostringstream& text) { buffer << text.str(); }
*/

namespace FileAndStreamExamples
{
    const string FILENAME = "test.dat";

    void Test()
    {
        // Create a file and write strings to it.
        {
            ofstream f;
            f.open(FILENAME, std::ios::out);

            f << "B\nD\nA\nB\nC";

            // endl flushes the buffer.
            f << endl;
        }

        // Read strings from a file.
        {
            auto f = ifstream{ FILENAME };
            if (f)
            {
                auto w = string{};
                while (std::getline(f, w))
                    cout << w;
                cout << " ";
            }
        }

        // Read strings from a file.
        {
            auto f = ifstream{ FILENAME };
            if (f) // check if the file has been read successfully
            {
                auto w = string{};
                while (f >> w) 
                    cout << w;
                cout << " ";
            }
        }

        // Read strings from a file and put them to a vector.
        {
            ifstream f(FILENAME);

            // Define an input iterator for the stream.
            std::istream_iterator<string> it(f);
            std::istream_iterator<string> eos;

            // Define a vector and initialize it to the source file.
            vector<string> v(it, eos);

            // Show the strings.
            for (auto& s : v)
                cout << s;
            cout << " ";
        }

        // Append a float value.
        {
            ofstream f;
            f.open(FILENAME, std::ios::out | std::ios::app);

            f << std::setiosflags(std::ios::fixed | std::ios::showpoint) << std::setprecision(6) << 7.1182; // 7.118200

            f << endl;
        }
    }
}
