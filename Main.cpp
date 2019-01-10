
#include "Arrays.h"
#include "AutoDecltypeTypedef.h"
#include "Casting.h"
#include "Classes.h"
#include "Containers.h"

//
// The purpose of this application is to provide examples of C++ and STL features.
//
int main()
{
    cout << "*** Arrays ***" << endl;
    Arrays();
    cout << endl << endl;

    cout << "*** Auto, Decltype, Typedef (type inference) ***" << endl;
    Auto(); Decltype(); Typedef();
    cout << endl << endl;

    cout << "*** Casting ***" << endl;
    Casting();
    cout << endl << endl;

    cout << "*** Classes ***" << endl;
    Classes();
    cout << endl << endl;

    cout << "*** Containers ***" << endl;
    Containers();
    cout << endl << endl;

    return 0;
}
