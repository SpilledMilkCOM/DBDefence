#include "pch.h"
#include "CppUnitTest.h"

#include "LoggerStdOut.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBDefenceConsoleCppTests {

    TEST_CLASS(LoggerStdOutTests) {

private:

public:

    TEST_METHOD(DeleteOptions_Succeeds_DeletesAllOptions) {
        LoggerStdOut* test = ConstructTestObject();

        Assert::IsNotNull(test, L"Not able to construct test object.");

        delete(test);
    }

private:

    LoggerStdOut* ConstructTestObject() {
        return NULL;
        //return new LoggerStdOut;
    }

    };
}
