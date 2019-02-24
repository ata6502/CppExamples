#pragma once

#include <iostream> // std::ostream
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm> // for_each, find_if, sort, etc.
#include <numeric> // std::accumulate
#include "Diagnostics.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;
using std::list;
using std::map;
using std::set;

/*
    *** Measure performance to ensure you are using the right collection ***
    *** Reserve storage in advance using the reserve method ***

    Write your code to make switching containers easy:
    - auto
    - begin() and end() global functions
    - algorithms

    Basic requirements for an object to be an element inside a standard container:
    - Copyable and/or moveable
    - Swappable
    - Comparable (optional)

    Types of iterators:
    https://docs.microsoft.com/en-us/cpp/standard-library/iterator
    https://docs.microsoft.com/en-us/cpp/standard-library/iterators
    - Output: forward moving, may store but not retrieve values, provided by ostream and inserter.
    - Input: forward moving, may retrieve but not store values, provided by istream.
    - Forward: forward moving, may store and retrieve values.
    - Bidirectional: forward and backward moving, may store and retrieve values, provided by list, set, multiset, map, and multimap.
    - Random access: elements accessed in any order, may store and retrieve values, provided by vector, deque, string, and array.

    Iterators are pointer-like abstractions. They minimize the dependencies between application code, algorithms, and containers.
    begin() and end() represent a half open range:
    - begin() points to the first element in the sequence
    - end() points to the last plus one element in the sequence

    Sorting and searching
    - Implemented as free functions.
    - The free functions take iterators to a collection as parameters.
    - Examples: for_each, find_if


    Sequence containers
    -------------------
    <vector> (sequence container)
    - Keeps elements in a continuous block of memory. 
    - Performs well for both iterating and random access.
    - Grows as needed when new items are added which can cause a lot of element copying. 
      Solution: ***pre-allocate memory when you create a vector container***. It also initializes all vector elements to 0.
    - You can keep smart pointers in your vector (copying pointers is cheap).
    - Compatible with C's memory model. You can pass a vector to a C-style API and it's binary layout will be compatible with the C-style array.

    <map> (associative container)
    - Keeps elements sorted to speed up searches.
    - Does not allow two values with the same key.
    - Provides the [] operator to add or access elements.
    - Provides a pair<> template to add elements.
    - Also called an associative array or a dictionary.

    <list> (sequence container)
    - A doubly-linked list.
    - Subscripting or random access is not provided. The list requires traversing.
    - In general, faster than <vector> for adding elements.
    - In general, slower than <vector> for accessing elements.
      ... but you need to measure and compare performance of vector vs. list
    - Elements are not copied when a new element is added.
    - In order to insert an element into a list the element position has to be found. This influences performance.

    <queue>, <deque>
    - FIFO
    - push/pop from one or both ends

    <priority_queue>
    - Bumps up a value to the front.


    Associative containers (provide lookup based on a key)
    ----------------------
    
    The following containers maintain an ordered of elements based on a comparison function typically less than:
    set<K>
    map<K, V>                   provides a container of key value pairs
    multiset<K>                 allows multiple elements with the same key i.e., it allows collisions; lookup based on a given key may result in 0, 1, or more elements
    multimap<K, V>              allows multiple elements with the same key

    The 'unordered' prefix is misleading. The following containers are hash containers. 
    The hash functions do not provide any particular ordering. This tends to provide faster lookup performance.
    unordered_set<K>
    unordered_map<K, V>
    unordered_multiset<K>
    unordered_multimap<K, V>
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
        // A vector of ints.
        vector<int> vec = { 1,2,3 };

        // range-based for (foreach) - the simplest way to iterate over the elements of a standard container
        for (auto n : vec)
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

        // Use global functions begin() and end()
        // - begin(vec) returns the first element in vec
        // - end(vec) returns the position after the last element in vec
        // - ++it increments the iterator
        // - *it returns a value that the iterator currently points to
        for (auto it = begin(vec); it != end(vec); ++it)
            cout << *it;
        cout << " ";

        // As above but more efficient. It determines the end iterator only once.
        for (auto it = begin(vec), _end = end(vec); it != _end; ++it)
            cout << *it;
        cout << " ";

        // Use member iterator methods begin() and end()
        // This is an old school and less flexible than using the global functions
        // as some containers may not have the begin() and end() method defined.
        for (auto it = vec.begin(), _end = vec.end(); it != _end; ++it)
            cout << *it;
        cout << " ";

        // Use const member iterator methods cbegin() and cend()
        for (auto it = vec.cbegin(), _end = vec.cend(); it != _end; ++it)
            cout << *it;
        cout << " ";

        // Use the reverse iterator. rbegin() points to the last element, rend() points to the one before first.
        for (auto it = std::rbegin(vec); it != std::rend(vec); ++it)
            cout << *it;
        cout << " ";

        // for_each algorithm with a lambda expression; you can specify a function name instead of lambda
        for_each(begin(vec), end(vec), [](int i) { cout << i; });
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

    class A 
    { 
    public:
        A() { cout << "A "; }
        ~A() { cout << "~A "; }
    };

    void VectorContainer()
    {
        // Create an empty vector.
        auto v1 = vector<int>{}; // invoke the default ctor

        // Check if the vector is empty.
        ASSERT(v1.empty());

        // Create a vector and initialize it with some element values.
        auto v2 = vector<int>{ 1,2,3 }; // invoke a param ctor

        // The size method returns the number of elements in the container.
        ASSERT(v2.size() == 3);

        // Create and initialize the vector with a sequence defined by a pair of iterators.
        // The sequence can be a C-style array, another vector, or another container type, such as a list.
        // Use the entire range from v2 to initialize the new vector.
        auto v3 = vector<int>{ begin(v2), end(v2) };
        ASSERT(v3.size() == 3);

        // Create and initialize the vector with a narrowed down sequence.
        auto v4 = vector<int>{ begin(v2)+1, end(v2)-1 };
        ASSERT(v4.size() == 1);
        ASSERT(v4[0] == 2);

        // Create a vector of 10 elements, where each element has the same value of 123. 
        auto v5 = vector<int>(10, 123);
        ASSERT(v5.size() == 10);
      
        auto v = vector<int>{ 1,2,3 };

        // Add an element using emplace_back.
        // emplace_back is analogous to the push_back method, but while push_back copies or moves the provided value into the container, 
        // emplace_back constructs the element in place by forwarding the arguments directly. emplace_back is a variadic function template.
        // It tends to be more efficient than push_back. 
        v.emplace_back(4);

        // Use the emplace method to insert an element anywhere in the container, although that is not as efficient for vector containers. 
        v.emplace(begin(v), 8); // insert a new value at the beginning of the sequence
      
        // 8,1,2,3,4
        for (auto i : v)
            cout << i;
        cout << " ";

        vector<float> values{ 1, 2, 3 }; // values automatically converted to float
        values.push_back(8);
        values.push_back(4.5f);
        values.pop_back(); // removes 4.5f

        // You can access elements of a vector using []. 
        // [] does not provide range checking.
        cout << values[3] << " "; // 8

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

        vector<A> a;
        A a1; // A()
        A a2; // A()

        a.push_back(a1); // use the A's copy ctor to copy a1 to a temp object that is inserted to the vector
        a.push_back(a2); // ~A(); we need a bigger vector; the temp object that holds a1 in the vector is destroyed and then a1 is copied again to the vector; then, the copy ctor is called to insert the a2 object to the vector
    } // ~A() ~A() - a1 and a2 destr; ~A() ~A() temp objects in the vector destr

    void ListContainer()
    {
        auto c = list<int>{}; // default ctor called

        ASSERT(c.empty());
        ASSERT(c.size() == 0);

        // Initialize the list with some values.
        c = list<int>{ 1, 2, 3, 4, 5 };

        ASSERT(!c.empty());
        ASSERT(c.size() == 5);

        // Initialize the list with a sequence defined by a pair of iterators.
        c = list<int>{ begin(c), end(c) };

        ASSERT(!c.empty());
        ASSERT(c.size() == 5);

        // The iterators provided by the list are bidirectional iterators, not random access 
        // iterators as is the case of vector. Bidirectional iterators allow you to move backward 
        // and forward by incrementing and decrementing.
        c = list<int>{ ++begin(c), --end(c) };

        ASSERT(c.size() == 3);

        // Use random access iterators provided by a vector to initialize a list.
        auto v = vector<int>{ 1, 2, 3 };
        c = list<int>{ begin(v) + 1, end(v) - 1 }; // initialize the list with the middle element in the vector

        ASSERT(c.size() == 1);

        // Access the first element in the list with the front method which returns a reference to the first element.
        ASSERT(c.front() == 2);

        // Create a list of 10 elements. Each element will have the element's default value. 
        c = list<int>(10);
        ASSERT(c.size() == 10);

        // Create a list of 10 integers with a specific value.
        c = list<int>(10, 123);
        ASSERT(c.size() == 10);

        c = list<int>{ 1, 2, 3, 4, 5 };

        // The list container provides constant time operations for inserting and deleting elements.

        // emplace_back inserts an element at the end of the list.
        c.emplace_back(6);

        // emplace_front inserts an element at the beginning of the list.
        c.emplace_front(0);

        // emplace inserts an element at a specific position given an iterator before which the new element will be constructed
        // i.e., the new element is always inserted before the given iterator.
        c.emplace(begin(c), -1);    // the same as emplace_front
        c.emplace(end(c), 7);       // the same as emplace_back

        for (auto e : c)
            cout << e;
        cout << " ";

        // Remove a single element or a range of elements given one or two iterators respectively.
        c.erase(begin(c));          // remove the first element

        // Remove the first element.
        c.pop_front();

        // Remove the last element.
        c.erase(--end(c));

        // Remove the last element.
        c.pop_back();

        ASSERT(c.size() == 5); // c = {1,2,3,4,5}

        // Remove all but the first and last elements. This erases the half-open range.
        c.erase(++begin(c), --end(c)); // c = {1,5}

        ASSERT(c.size() == 2);
        ASSERT(c.front() == 1);
        ASSERT(c.back() == 5);

        // Insert a sequence defined using an initializer list.
        c.insert(++begin(c), { 2, 3, 4 });

        // In case of lists, iterators remain valid across reverse, sort, and other such operations. 
        auto pos = ++begin(c);      // get an iterator to the list's second element
        ASSERT(*pos == 2);          // the value of the second element is 2

        // Reverse the order of the elements.
        c.reverse();

        // After reversing the pos iterator still points to the same element, 
        // even though the element is now in a different position in the sequence. 
        ASSERT(*pos == 2);

        // Sort the elements. By default, sort uses the less than as its sort operator, 
        // but you can provide your own comparison function. 
        c.sort();

        // After sorting the pos iterator still points to the same element.
        ASSERT(*pos == 2);

        // Remove all odd numbers from the list.
        c.remove_if([](int value)
        {
            return value & 1;
        });

        for (auto e : c)
            cout << e;
        cout << " ";
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
        for (const auto& p : histogram) // p is an std::pair
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
        for (const auto& b : books)
            cout << b.first << b.second.Title << b.second.Author << " ";

        // Find an element using the find function.
        // The find function returns an iterator to a found element.
        auto b1 = books.find(2);
        cout << "Found1:" << b1->first << b1->second.Title << b1->second.Author << " ";

        // Obtain an element using [] rather than the find() function.
        auto b2 = books[2];
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
        int n = 0;

        // Copy all elements of a vector to another vector.
        auto nv = vec;

        // Sort a container in-place.
        sort(begin(vec), end(vec));

        cout << "sorted:";
        for (auto n : vec)
            cout << n; // 1 2 3 3 4 5
        cout << " ";

        // Count how many 3s are in container.
        auto cnt = count(begin(vec), end(vec), 3);
        cout << cnt << " "; // 2

        // Obtain unique elements.
        vector<int> vec_copy;
        unique_copy(vec.begin(), vec.end(), std::back_inserter(vec_copy));

        cout << "unique:";
        for (auto n : vec_copy)
            cout << n; // 1 2 3 4 5
        cout << " ";

        // Accumulate numers.
        float sum = std::accumulate(begin(vec), end(vec), 0.0f);
        cout << "sum:" << sum << " "; // 1+2+3+3+4+5 = 18

        // Accumulate strings.
        vector<string> sv{ "a", "b", "c" };
        string abc = std::accumulate(begin(sv), end(sv), string(">")); // the 3rd arg is a starting value
        cout << "abc:" << abc << " ";

        // Accumulate strings with separators.
        string abc2 = std::accumulate(begin(sv), end(sv), string(">"), [](string a, string b) { return a + "," + b; }); // PRB: inserts a comma at the beginning
        cout << "abc:" << abc2 << " ";

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

        // Find all odd elements. Output: 1335 (sorted because we called std::sort).
        auto odd = find_if(vec.begin(), vec.end(), [](int n) { return n % 2; });
        while (odd != vec.end())
        {
            cout << *odd;
            odd = find_if(++odd, vec.end(), [](int n) { return n % 2; }); // ++odd is the next iterator
        }

        // Populate a vector with five values using std::generate
        v = vector<int>(5);
        n = 1;
        std::generate(begin(v), end(v), [&n] { return n++; }); // v = {1,2,3,4,5}
        
        // Insert five values at the end of a vector using std::generate_n
        v = vector<int>(5);
        n = 1;
        std::generate_n(std::back_inserter(v), 5, [&]() { return n++; }); // v = {0,0,0,0,0,1,2,3,4,5}
    }

    void RemovingElements()
    {
        vector<int> v = { 3,4,1,3,2,5 };

        auto v1 = v;

        // Remove all 3's using the remove_if algorithm.
        auto new_end = std::remove_if(begin(v1), end(v1), [](int elem) { return (elem == 3); });

        // At this point v1 still has 6 elements: 4,1,2,5,2,5
        // The 2,5 at the end are the old elements before erasing 3's.

        v1.erase(new_end, end(v1));
        // After calling erase, v1 contains 4 elements: 4,1,2,5

        auto v2 = v;

        // More compact - in a single line.
        v2.erase(std::remove_if(begin(v2), end(v2), [](int elem) { return (elem == 3); }), end(v2));
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
        ListContainer();
        SetContainer();
        MapContainer();
        ContainerAlgorithms();
        RemovingElements();
        Vector2D();
    }
}