
#include <windows.h> // used in some usage demonstrations
#undef max // undefine the max macro because it interferes with std::numeric_limits<int>::max()

#include "Arrays.h"
#include "AutoDecltypeTypedef.h"
#include "Casting.h"
#include "Classes.h"
#include "Containers.h"
#include "Conversion.h"
#include "Diagnostics.h"
#include "Enums.h"
#include "Exceptions.h"
#include "FilesAndStreams.h"
#include "Formatting.h"
#include "Initialization.h"
#include "Input.h"
#include "Lambda.h"
#include "MoveSemantics.h"
#include "Numbers.h"
#include "OperatorOverloading.h"
#include "PointersAndReferences.h"
#include "Rand.h"
#include "SmartClasses.h"
#include "SmartPointers.h"
#include "Strings.h"
#include "Templates.h"

#include "Recursion\RecursionTest.h"
#include "Applications\Histogram.h"
#include "Patterns\Account.h"

//
// The purpose of this application is to provide examples of C++ and STL features.
//
// Simple rules:
// - Use local scope (stack semantics) as much as you can.
// - If you need to use the free store, use smart pointers.
//
int main()
{
    cout << "*** Arrays ***" << endl;
    ArraysExamples::Test();
    cout << endl << endl;

    cout << "*** Auto, Decltype, Typedef (type inference) ***" << endl;
    AutoExamples::Test();
    DecltypeExamples::Test(); 
    TypedefExamples::Test();
    cout << endl << endl;

    cout << "*** Casting ***" << endl;
    Casting();
    cout << endl << endl;

    cout << "*** Classes ***" << endl;
    ClassesExamples::Test();
    cout << endl << endl;

    cout << "*** Containers ***" << endl;
    ContainerExamples::Containers();
    cout << endl << endl;

    cout << "*** Conversion ***" << endl;
    ConversionExamples::Conversion();
    cout << endl << endl;

    cout << "*** Diagnostics ***" << endl;
    Diagnostics::Test();
    cout << endl << endl;

    cout << "*** Enums ***" << endl;
    Enums();
    cout << endl << endl;

    cout << "*** Exceptions ***" << endl;
    ExceptionsExamples::Exceptions();
    cout << endl << endl;

    cout << "*** Files & Streams ***" << endl;
    FilesAndStreamsExamples::FilesAndStreams();
    cout << endl << endl;

    cout << "*** Formatting ***" << endl;
    FormattingExamples::Formatting();
    cout << endl << endl;

    cout << "*** Initialization ***" << endl;
    InitializationExamples::Initialization();
    cout << endl << endl;

    //cout << "*** Input ***" << endl;
    //InputExamples::Input();
    //cout << endl << endl;

    cout << "*** Lambda ***" << endl;
    LambdaExamples::Test();
    cout << endl << endl;

    cout << "*** Move Semantics ***" << endl;
    MoveSemanticsExamples::Test();
    cout << endl << endl;

    cout << "*** Operator overloading ***" << endl;
    OperatorOverloadingExamples::OperatorOverloading();
    cout << endl << endl;

    cout << "*** Numbers ***" << endl;
    NumbersExamples::Numbers();
    cout << endl << endl;

    cout << "*** Pointers & References ***" << endl;
    PointersAndReferencesExamples::PointersAndReferences();
    cout << endl << endl;

    cout << "*** Rand ***" << endl;
    RandExamples::Rand();
    cout << endl << endl;

    cout << "*** Smart Classes ***" << endl;
    SmartClassesExamples::Test();
    cout << endl << endl;

    cout << "*** Smart Pointers ***" << endl;
    SmartPointersExamples::Test();
    cout << endl << endl;

    cout << "*** Strings ***" << endl;
    StringsExamples::Test();
    cout << endl << endl;

    cout << "*** Templates ***" << endl;
    TemplatesExamples::Templates();
    cout << endl << endl;

    // RecursionTest();
    // Applications::Histogram();
    // Patterns::pImplTest();

    return 0;
}
