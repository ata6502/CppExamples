#pragma once

#include <iostream>

using std::cout;
using std::endl;

/*
    Tower of Hanoi

    1. Move n-1 disks from Source to Temp, using Dest as a temporary holding area.
    2. Move the last disk (the largest) from Source to Dest.
    3. Move the n-1 disks from Temp to Dest, using Source as a temporary holding area.

    Sample output:

    The number of disks: 3
    1 -> 3
    1 -> 2
    3 -> 2
    1 -> 3
    2 -> 1
    2 -> 3
    1 -> 3
*/

void towerOfHanoi(int num, int source, int dest, int temp)
{
    if (num > 0)
    {
        towerOfHanoi(num - 1, source, temp, dest);
        cout << source << " -> " << dest << endl;
        towerOfHanoi(num - 1, temp, dest, source);
    }
}

void TowerOfHanoi()
{
    cout << "*** Tower of Hanoi ***" << endl;

    int num = 3;     // the number of disks to be moved; modify this value to have a tower of a different height

    // labels for the pegs
    int source = 1;  // the peg on which the disks are initially threaded
    int dest = 3;    // the peg to which the disks are to be moved
    int temp = 2;    // the peg used as a temporary holding area

    towerOfHanoi(num, source, dest, temp);

    cout << endl;
}
