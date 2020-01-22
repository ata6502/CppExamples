#include "Containers.h"

#include <iostream>
#include <string>
#include <iterator> // std::back_inserter, std::istream_iterator
#include <conio.h> // getch()

using std::cout;
using std::endl;
using std::string;

namespace Applications
{
    // PrintHistogram outputs histogram data.
    void PrintHistogram(const std::pair<const string, int> r)
    {
        cout << r.first << ' ' << r.second << endl;
    }

    // Read words from input and record the frequency of their occurrence. 
    void Histogram()
    {
        using std::istream_iterator;

        cout << endl << "Do you want to run histogram? (y/n)" << endl;
        char answer = _getch();
        if (answer == 'n' || answer == 'N')
            return;

        cout << "Enter words and mark the end with CTRL-Z." << endl;

        // The histogram stores the words and their frequency.
        map<string, int> histogram;

        // Create a stream iterator using the default ctor. The stream iterator created 
        // this way represents a special value (end-of-file or error).
        istream_iterator<string> eos;  // CTRL-Z + Enter

        // Create a stream iterator using a constructor that accepts a stream.
        // The stream iterator created this way stops processing when the special value 
        // is encountered.
        istream_iterator<string> ii(std::cin);

        // Register the frequency of an input string s starting from the current position 
        // in the stream (which is the beginning) to the special value (which indicates the end).
        for_each(ii, eos, [&histogram](string s) { histogram[s]++; });

        // Print each element of the histogram.
        for_each(histogram.begin(), histogram.end(), PrintHistogram);
    }
}