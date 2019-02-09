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

/*
    - The stream insertion operation (<<) is used for concatenating (also called 'chaining' or 'cascading') the input streams.
    - Streams are not copyable; they should be passed by reference, for example: void AddToBuffer(const std::wostringstream& text) { buffer << text.str(); }
*/

namespace FilesAndStreamsExamples
{
    const string FILENAME = "test.dat";
    const string ANOTHERFILE = "test2.dat";

    void FilesAndStreams()
    {
        // 
        // Create a file and write strings to it.
        //
        std::ofstream file;
        file.open(FILENAME, std::ios::out); 

        file << "B\nD\nA\nB\nC" << endl; // ??? does endl flush the stream?

        file.flush();
        file.close();


        //
        // Read strings from the file.
        //
        // Define an input stream that can be attached to a file.
        std::ifstream inStream(FILENAME);

        // Define an input iterator for the stream.
        std::istream_iterator<string> inIter(inStream);
        std::istream_iterator<string> eos;

        // Define a vector and initialize it to the source file.
        vector<string> v(inIter, eos);

        // Show sorted strings from the file.
        std::sort(v.begin(), v.end());
        for (auto& s : v)
            cout << s;
        cout << " ";


        //
        // Write to another file using ostream_iterator.
        //
        // Define an output stream that can be attached to a file.
        std::ofstream outStream(ANOTHERFILE);

        // Define an output iterator for the stream.
        std::ostream_iterator<string> outIter(outStream, "\n");

        // Eliminate duplicates and write the result to another file
        std::unique_copy(v.begin(), v.end(), outIter);

        outStream.flush();
        outStream.close();


        //
        // Append a float value to a file.
        //
        file.open(ANOTHERFILE, std::ios::out | std::ios::app);

        file << std::setiosflags(std::ios::fixed | std::ios::showpoint) << std::setprecision(6) << 7.1182 << std::endl; // 7.118200

        file.flush();
        file.close();


        //
        // StringBuilder
        //
        std::ostringstream oss;
        oss << "a:" << 1 << ",";
        oss << "b:" << 2.2;

        // str() puts everything together and gives a string
        string text = oss.str();
        cout << text << " ";
    }
}
