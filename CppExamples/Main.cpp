
#include "Arrays.h"
#include "AutoDecltypeTypedef.h"
#include "Casting.h"
#include "Chrono.h"
#include "Classes.h"
#include "Containers.h"
#include "Conversion.h"
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
#include "RegularExpressions.h"
#include "SmartPointers.h"
#include "Strings.h"
#include "Templates.h"

//
// The purpose of this application is to provide examples of C++ and STL features.
//
int main()
{
    cout << "*** Arrays ***" << endl;
    ArraysExamples::Test();
    cout << endl << endl;

    cout << "*** Auto, Decltype, Typedef (type inference) ***" << endl;
    AutoDecltypeExamples::Test();
    TypedefExamples::Test();
    cout << endl << endl;

    cout << "*** Casting ***" << endl;
    CastingExamples::StaticCast();
    CastingExamples::DynamicCast();
    CastingExamples::ConstCast();
    CastingExamples::ReinterpretCast();
    cout << endl << endl;

    cout << "*** Chrono ***" << endl;
    ChronoExamples::Test();
    cout << endl << endl;

    cout << "*** Classes ***" << endl;
    ClassesExamples::Test();
    cout << endl << endl;

    cout << "*** Containers ***" << endl;
    ContainerExamples::Test();
    cout << endl << endl;

    cout << "*** Conversion ***" << endl;
    ConversionExamples::Test();
    cout << endl << endl;

    cout << "*** Enums ***" << endl;
    EnumExamples::Test();
    cout << endl << endl;

    cout << "*** Exceptions ***" << endl;
    ExceptionsExamples::Test();
    cout << endl << endl;

    cout << "*** Files & Streams ***" << endl;
    FileAndStreamExamples::Test();
    cout << endl << endl;

    cout << "*** Formatting ***" << endl;
    FormattingExamples::Test();
    cout << endl << endl;

    cout << "*** Initialization ***" << endl;
    InitializationExamples::Initialization();
    cout << endl << endl;

    //cout << "*** Input ***" << endl;
    //InputExamples::Test();
    //cout << endl << endl;

    cout << "*** Lambda ***" << endl;
    LambdaExamples::Test();
    cout << endl << endl;

    cout << "*** Move semantics ***" << endl;
    MoveSemanticsExamples::Test();
    cout << endl << endl;

    cout << "*** Operator overloading ***" << endl;
    OperatorOverloadingExamples::OperatorOverloading();
    cout << endl << endl;

    cout << "*** Numbers ***" << endl;
    NumbersExamples::Test();
    cout << endl << endl;

    cout << "*** Pointers & References ***" << endl;
    PointersAndReferencesExamples::PointersAndReferences();
    cout << endl << endl;

    cout << "*** Rand ***" << endl;
    RandExamples::Rand();
    cout << endl << endl;

    cout << "*** Regular expressions ***" << endl;
    RegularExpressions::Test();
    cout << endl << endl;

    cout << "*** Smart pointers ***" << endl;
    SmartPointersExamples::Test();
    cout << endl << endl;

    cout << "*** Strings ***" << endl;
    StringsExamples::Test();
    cout << endl << endl;

    cout << "*** Templates ***" << endl;
    TemplatesExamples::Templates();
    cout << endl << endl;

    return 0;
}
