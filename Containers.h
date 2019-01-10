#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // for_each
#include <numeric> // std::accumulate

using std::cout;
using std::endl;
using std::vector;
using std::map;

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

void ContainerIteration()
{
    vector<int> vec = { 1,2,3,4 };

    // range-based for (foreach)
    for (auto n : vec)
        cout << n;
    cout << " ";

    // for loop
    for (unsigned int i = 0; i < vec.size(); ++i)
        cout << vec[i];
    cout << " ";

    // iterator
    // - begin(vec) returns the first element in vec
    // - end(vec) returns the position after the last element in vec
    // - ++it increments the iterator
    // - *it returns a value that the iterator currently points to
    for (auto it = begin(vec); it != end(vec); ++it)
        cout << *it;
    cout << " ";

    // for_each algorithm with a lambda expression; it could be a function name instead of lambda
    for_each(vec.begin(), vec.end(), [](int i) { cout << i; });
    cout << " ";
}

void ContainerOperations()
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
    auto pv = find_if(vec.begin(), vec.end(), [](int i) { return (i % 5 == 0); });
    cout << "found:" << *pv << " ";
}

struct Book { int Id; string Title; string Author; };

void MapContainer()
{
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
    ContainerOperations();
    MapContainer();
    Vector2D();
}