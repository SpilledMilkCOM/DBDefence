#include "pch.h"
#include "CppUnitTest.h"

// Need to also link in the ArgumentParser.obj
#include "../DBDefence.ConsoleCpp/ArgumentParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBDefenceConsoleCppTests {

    TEST_CLASS(ArgumentParserTests) {
private:

    const string TEST_OPTION = "-a";
    const string TEST_OPTION_VALUE_NAME = "aValue";
    const string TEST_OPTION_DESCRIPTION = "This is 'a' Value description";
    const string TEST_OPTION2 = "-b";
    const string TEST_OPTION2_VALUE_NAME = "bValue";
    const string TEST_OPTION2_DESCRIPTION = "This is 'b' Value description";
    const string TEST_OPTION_WRONG = "-w";

public:
    TEST_METHOD(AddOption_Succeeds_AddsAnOption) {
        // AddOption() is done in the construct utility
        ArgumentParser* test = ConstructTestObjectWithOptions();

        char* argv[] = { "C:\\tmp\\program.exe",  "-a", "Avalue", "-b", "Bvalue" };

        test->Parse(5, argv);

        Assert::IsTrue(test->HasOption(TEST_OPTION), L"The option should have been added");
        Assert::IsTrue(test->HasOption(TEST_OPTION2), L"The option should have been added");
    }

    TEST_METHOD(HasOption_ReturnsFalse_WithNoOptionsInList) {
        ArgumentParser* test = ConstructTestObject();

        Assert::IsFalse(test->HasOption(TEST_OPTION), L"The option should not exist");
    }

    TEST_METHOD(HasOption_ReturnsFalse_FindingWrongOption) {
        ArgumentParser* test = ConstructTestObjectWithOptions();

        Assert::IsFalse(test->HasOption(TEST_OPTION_WRONG), L"The option should not exist");
    }

    TEST_METHOD(HasOption_ReturnsTrue_FindingCorrectOption) {
        ArgumentParser* test = ConstructTestObjectWithOptions();

        char* argv[] = { "C:\\tmp\\program.exe",  "-a", "Avalue", "-b", "Bvalue" };

        test->Parse(5, argv);

        Assert::IsTrue(test->HasOption(TEST_OPTION), L"The option should exist");
    }

    TEST_METHOD(Parse_Succeeds_AbleToRetrieveValuesByOption) {
        ArgumentParser* test = ConstructTestObjectWithOptions();
        char* argv[] = { "C:\\tmp\\program.exe",  "-a", "Avalue", "-b", "Bvalue" };

        test->Parse(5, argv);

        Assert::AreEqual(string(argv[2]), test->GetValue(TEST_OPTION), L"The option was not parsed correctly");
        Assert::AreEqual(string(argv[4]), test->GetValue(TEST_OPTION2), L"The option was not parsed correctly");
    }

private:

    ArgumentParser* ArgumentParserTests::ConstructTestObject() {
        return new ArgumentParser("TestProgram");
    }

    ArgumentParser* ArgumentParserTests::ConstructTestObjectWithOptions() {
        // Return a pointer because the destruction should NOT be called since those options will be deallocated with it.

        ArgumentParser* result = new ArgumentParser("TestProgram");
        bool required = true;

        result->AddOption(new ArgumentOption(TEST_OPTION, TEST_OPTION_VALUE_NAME, TEST_OPTION_DESCRIPTION, required));
        result->AddOption(new ArgumentOption(TEST_OPTION2, TEST_OPTION2_VALUE_NAME, TEST_OPTION2_DESCRIPTION, required));

        return result;
    }

    };
}
