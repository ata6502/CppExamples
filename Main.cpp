
#include "Arrays.h"
#include "AutoDecltypeTypedef.h"
#include "Casting.h"
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
#include "Numbers.h"
#include "Rand.h"

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
    ContainerExamples::Containers();
    cout << endl << endl;

    cout << "*** Conversion ***" << endl;
    ConversionExamples::Conversion();
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
    LambdaExamples::Lambda();
    cout << endl << endl;

    cout << "*** Numbers ***" << endl;
    NumbersExamples::Numbers();
    cout << endl << endl;

    cout << "*** Rand ***" << endl;
    RandExamples::Rand();
    cout << endl << endl;

    return 0;
}
