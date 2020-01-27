
#include "Diagnostics.h"
#include "SmartClasses.h"

int main()
{
    cout << "*** Diagnostics ***" << endl;
    Diagnostics::Test();
    cout << endl << endl;

    cout << "*** Smart classes ***" << endl;
    SmartClassesExamples::Test();
    cout << endl << endl;

    return 0;
}
