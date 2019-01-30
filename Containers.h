#pragma once

#include <iostream> // std::ostream
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm> // for_each
#include <numeric> // std::accumulate

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;
using std::map;
using std::set;

/*
    <vector>
    - Keeps elements in a continuous block of memory.

    <map>
    - Keeps elements sorted to speed up searches.
    - Provides the [] operator to add or access elements.
    - Provides a pair<> template to add elements.
    - Also called an associative array or a dictionary.

    <list>
    - A doubly-linked list.
    - faster than <vector> for adding elements.
    - slower than <vector> for accessing elements.

    <queue>, <deque>
    - FIFO
    - push/pop from one or both ends
    - priority-queue

    <set>
    - Does not need to reorganize itself whenever elements are added or removed.
      It means you can keep iterators going over a set, even when adding/removing
      elements.
    - Functions: union, intersection, difference.

    <multimap>
    - A map that can have multiple values as a key.
*/

namespace ContainerExamples
{
    // The range-based for loop iterates over elements of a given range, array, or collection.
    // for (declaration : collection)
    // {
    //     statement
    // }
    void ContainerIteration()
    {
        vector<int> vec = { 1,2,3 };

        // range-based for (foreach)
        for (auto& n : vec)
            cout << n;
        cout << " ";

        // To avoid calling the copy constructor and the destructor for each element, 
        // you should usually declare the current element to be a constant reference.
        for (const auto& n : vec)
            cout << n;
        cout << " ";

        // If you need to modify an element in a range-for loop, use a reference as 
        // the element variable.
        for (int& n : vec)
            ++n;
        for (int n : vec)
            cout << n;
        cout << " ";

        // Multiply each element of a vector by 3.
        // Declaring n as a reference is important because otherwise the statements in the body of the
        // for loop act on a local copy of the elements in the vector (which sometimes also might be useful).
        for (auto& n : vec)
            n *= 2;

        // for loop
        for (unsigned int i = 0; i < vec.size(); ++i)
            cout << vec[i];
        cout << " ";

        // iterator - using global functions begin() and end()
        // - begin(vec) returns the first element in vec
        // - end(vec) returns the position after the last element in vec
        // - ++it increments the iterator
        // - *it returns a value that the iterator currently points to
        for (auto it = begin(vec); it != end(vec); ++it)
            cout << *it;
        cout << " ";

        // iterator - as above but more efficient; it determines the end iterator
        // only once.
        for (auto it = begin(vec), _end = end(vec); it != _end; ++it)
            cout << *it;
        cout << " ";

        // iterator - using member iterator methods begin() and end()
        for (auto it = vec.begin(), _end = vec.end(); it != _end; ++it)
            cout << *it;
        cout << " ";

        // iterator - using const member iterator methods cbegin() and cend()
        for (auto it = vec.cbegin(), _end = vec.cend(); it != _end; ++it)
            cout << *it;
        cout << " ";

        // reverse iterator - rbegin() points to the last element
        for (auto it = vec.rbegin(); it != vec.rend(); ++it)
            cout << *it;
        cout << " ";

        // for_each algorithm with a lambda expression; it could be a function name instead of lambda
        for_each(vec.begin(), vec.end(), [](int i) { cout << i; });
        cout << " ";

        // Iterate over an initializer list..
        for (int i : { 1, 2, 3 })
            cout << i;
        cout << " ";

        // Use a C-style array of known size.
        int array[] = { 1, 2, 3 };
        int sum = 0; // the sum of all elements
        for (int x : array)
            sum += x;
        for (auto elem : { sum, sum * 2, sum * 4 }) // print some multiples of sum
            cout << elem << ",";
        cout << " ";
    }

    // Used in ContainerIterationUsingGenericFunction().
    // A generic function to print all elements of a collection. 
    // To avoid calling the copy constructor and the destructor for each element, 
    // declare the current element to be a constant reference.
    template <typename T>
    void PrintElements(const T& coll)
    {
        for (const auto& elem : coll)
        {
            cout << elem;
        }
        cout << " ";
    }

    void ContainerIterationUsingGenericFunction()
    {
        vector<int> vec = { 4,3,2,1 };
        PrintElements(vec);
    }

    void VectorContainer()
    {
        vector<float> values{ 1, 2, 3 }; // values automatically converted to float
        values.push_back(4.5f);
        values.push_back(8);
        values.pop_back(); // removes 8

        // std::vector performs range checking when you use at()
        // if an index is out of range, an exception is thrown
        try 
        {
            float u = values.at(5); // index 5 is out of range
        }
        catch (const std::out_of_range& exc)
        {
            cout << "\"" << exc.what() << "\" ";
        }
    }

    void SetContainer()
    {
        string text("to be, or not to be, that is the question");

        set<char> letters;
        for (char c : text)
        {
            if (isalpha(c)) 
                letters.insert(c);
        }

        // output: abehinoqrstu - a sorted list (? this is a set, not list) of letters
        for (char c : letters)
            cout << c;
        cout << " ";
    }

    struct Book 
    { 
        int Id; 
        string Title; 
        string Author; 
    };

    void MapContainer()
    {
        //
        // Histogram
        //
        string text("to be, or not to be");

        // char is a key
        // int is a value
        map<char, int> histogram;

        for (char c : text)
        {
            if (isalpha(c)) 
                histogram[c]++; // if the values of c does not exist, it will be added to the histogram and initialized with the default value
        }

        // Show the keys and values. Note that the pairs are sorted by the key.
        for (auto p : histogram) // p is an std::pair
            cout << p.first << ":" << p.second << " ";


        //
        // Add elements, iterate over map, find an element, get an element
        //
        auto book1 = Book{ 1, "X", "A" };
        auto book2 = Book{ 3, "Z", "C" };
        auto book3 = Book{ 2, "Y", "B" };

        map<int, Book> books;

        // Add elements using [].
        books[book1.Id] = book1;
        books[book2.Id] = book2;

        // Add an element using the pair<> template. Note that the book3 
        // is inserted between book1 and book2. This preserves the book order by the key.
        std::pair<int, Book> p(book3.Id, book3);
        books.insert(p);

        // Iterate through the entire map.
        for (auto p : books)
            cout << p.first << p.second.Title << p.second.Author << " ";

        // Find an element using the find function.
        // The find function returns an iterator to a found element.
        auto b1 = books.find(2);
        cout << "Found1:" << b1->first << b1->second.Title << b1->second.Author << " ";

        // Obtain an element using [].
        auto b2 = books[1];
        cout << "Found2:" << b2.Id << b2.Title << b2.Author << " ";
    }

    struct Person
    {
        string Name;
        int Age;

        friend ostream& operator<<(ostream& os, const Person& p)
        {
            return os << p.Name << p.Age << " ";
        }
    };

    void ContainerAlgorithms()
    {
        vector<int> vec = { 3,4,1,3,2,5 };

        // Sort a container in-place.
        sort(begin(vec), end(vec));

        cout << "sorted:";
        for (auto n : vec)
            cout << n; // 1 2 3 3 4 5
        cout << " ";

        // Count how many 3s are in container.
        auto n = count(begin(vec), end(vec), 3);
        cout << n << " "; // 2

        // Obtain unique elements.
        vector<int> vec_copy;
        unique_copy(vec.begin(), vec.end(), std::back_inserter(vec_copy));

        cout << "unique:";
        for (auto n : vec_copy)
            cout << n; // 1 2 3 4 5
        cout << " ";

        // Accumulate values.
        float sum = accumulate(vec.begin(), vec.end(), 0.0f);
        cout << "sum:" << sum << " "; // 1+2+3+3+4+5 = 18

        // Find an element that fulfills a given predicate (a lambda).
        // find_if returns an iterator to the found element.
        auto pv = std::find_if(
            vec.begin(), 
            vec.end(), 
            [](int i) { return (i % 5 == 0); });
        if (pv != vec.end())
            cout << "found:" << *pv << " ";

        vector<Person> people{ { "A", 1 }, { "B", 3 }, { "C", 5 } };

        auto printAllPeople = [&people]()
        {
            // for_each takes iterators and applies a function to each element
            std::for_each(begin(people), end(people),
                [](const Person& p) { cout << p; });
        };

        printAllPeople();

        // max_element returns an iterator
        auto oldestPerson_it = std::max_element(
            people.begin(),
            people.end(),
            [](const Person& a, const Person& b) { return a.Age < b.Age; } // a predicate
        );

        // Obtain the person for the iterator by using *
        cout << *oldestPerson_it; // C5

        // Find a person.
        auto person_it = std::find_if(
            people.begin(), 
            people.end(),
            [](const Person& p) { return p.Name == string("B"); }); // the string wrapper is optional

        if (person_it != people.end()) // check if anything was found
            // treat the iterator as a pointer
            cout << person_it->Name << " "; // B

        // Count the number of people.
        auto youngerThan5 = std::count_if(
            people.begin(),
            people.end(),
            [](const Person& p) { return p.Age < 5; });
        cout << youngerThan5 << " "; // 2

        // Replace a person: C5 --> X2
        Person x{ "X", 2 };
        std::replace_if(
            people.begin(), 
            people.end(),
            [](const Person& p) { return p.Name == "C"; },
            x);
        printAllPeople();

        // Sort by age (ascending)
        // In descending order: replace a.Age < b.Age with a.Age > b.Age
        std::sort(
            people.begin(), 
            people.end(),
            [](const Person& a, const Person& b) { return a.Age < b.Age; });
        printAllPeople();

        // Run permutations until all combinations are exhausted. In such a case,
        // next_permutation will return false.
        vector<int> v{ 1, 2, 3, 4 };
        std::next_permutation(v.begin(), v.end());
        for (auto i : v) 
            cout << i;
        cout << " ";
        std::next_permutation(v.begin(), v.end());
        for (auto i : v)
            cout << i;
        cout << " ";
    }

    void Vector2D()
    {
        // Field dimensions 5x3=15
        long rows = 5, cols = 3;
        vector<vector<int>> field(rows);

        // Reserve memory for columns.
        for (int i = 0; i < rows; ++i)
            field[i].resize(cols);

        // Fill the field.
        int x, y, n = 0;
        for (x = 0; x < rows; ++x)
        {
            for (y = 0; y < cols; ++y)
            {
                field[x][y] = n;
                ++n;
            }
        }
    }

    void Containers()
    {
        ContainerIteration();
        ContainerIterationUsingGenericFunction();
        VectorContainer();
        SetContainer();
        MapContainer();
        ContainerAlgorithms();
        Vector2D();
    }
}