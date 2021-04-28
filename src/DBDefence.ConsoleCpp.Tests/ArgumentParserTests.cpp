#include "pch.h"
#include "CppUnitTest.h"

// Need to also link in the ArgumentParser.obj
#include "ArgumentParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DBDefenceConsoleCppTests {

    TEST_CLASS(ArgumentParserTests) {

private:

    const string PROGRAM_NAME = "TestProgram";
    const string TEST_OPTION = "-a";
    const string TEST_OPTION_VALUE_NAME = "aValue";
    const string TEST_OPTION_DESCRIPTION = "This is 'a' Value description";
    const string TEST_OPTION2 = "-b";
    const string TEST_OPTION2_VALUE_NAME = "bValue";
    const string TEST_OPTION2_DESCRIPTION = "This is 'b' Value description";
    const string TEST_OPTION_WRONG = "-w";

public:

    TEST_METHOD(DeleteOptions_Succeeds_DeletesAllOptions) {
        ArgumentParser* test = ConstructTestObjectWithOptions();

        test->DeleteOptions();

        string actual = test->Usage();

        Assert::AreEqual(string("Usage: " + PROGRAM_NAME + " \n\n[]  Argument is optional."), actual, L"The usage text did not match");
    }

    TEST_METHOD(AddOption_Succeeds_AddsAnOption) {
        // AddOption() is done in the construct utility
        ArgumentParser* test = ConstructTestObjectWithOptions();

        char* argv[] = { "C:\\tmp\\program.exe",  "-a", "Avalue", "-b", "Bvalue" };

        test->Parse(5, argv);

        Assert::IsTrue(test->HasOption(TEST_OPTION), L"The option should have been added");
        Assert::IsTrue(test->HasOption(TEST_OPTION2), L"The option should have been added");
    }

    TEST_METHOD(DumpArgs_Displays_RepresentativeArguments) {
        ArgumentParser* test = ConstructTestObject();
        char* argv[] = { "C:\\tmp\\program.exe",  "-a", "Avalue", "-b", "Bvalue" };

        string actual = test->DumpArgs(5, argv);

        Assert::AreEqual(string("argc=5\nargv[0]=C:\\tmp\\program.exe\nargv[1]=-a\nargv[2]=Avalue\nargv[3]=-b\nargv[4]=Bvalue\n"), actual, L"The usage text did not match");
    }

    TEST_METHOD(GetValue_ThrowsException_WhenValueIsNotProvided) {
        ArgumentParser* test = ConstructTestObjectWithOptions();
        char* argv[] = { "C:\\tmp\\program.exe",  "-a", "-b", "Bvalue" };
        bool exceptionThrown = false;

        test->Parse(4, argv);

        try {
            test->GetValue(TEST_OPTION);

        } catch (...) {
            exceptionThrown = true;
        }

        Assert::IsTrue(exceptionThrown, L"Exception was not thrown.");

        // Could not wrap this up sufficiently.  :(

        // Assert::ExpectException<exception, string>(test->GetValue(TEST_OPTION));
    }

    TEST_METHOD(GetValue_ThrowsSpecificException_WhenValueIsNotProvided) {
        ArgumentParser* test = ConstructTestObjectWithOptions();
        char* argv[] = { "C:\\tmp\\program.exe",  "-a", "-b", "Bvalue" };
        bool exceptionThrown = false;
        string message;

        test->Parse(4, argv);

        try {
            test->GetValue(TEST_OPTION);

        } catch (exception* ex) {
            exceptionThrown = true;
            if (ex != NULL) {
                message = ex->what();
           }
        }

        Assert::IsTrue(exceptionThrown, L"Exception was not thrown.");
        Assert::AreEqual("The option '" + TEST_OPTION + "' is required.", message, L"Exception was not thrown.");
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

        string actualOption = test->GetValue(TEST_OPTION);
        string actualOption2 = test->GetValue(TEST_OPTION2);

        Assert::AreEqual(string(argv[2]), actualOption, L"The option was not parsed correctly");
        Assert::AreEqual(string(argv[4]), actualOption2, L"The option was not parsed correctly");
    }

    TEST_METHOD(Usage_Displays_WithNoOptionsInList) {
        ArgumentParser* test = ConstructTestObject();

        string actual = test->Usage();

        Assert::AreEqual(string("Usage: " + PROGRAM_NAME + " \n\n[]  Argument is optional."), actual, L"The usage text did not match");
    }

    TEST_METHOD(Usage_Displays_WithCorrectOptions) {
        ArgumentParser* test = ConstructTestObjectWithOptions();

        string actual = test->Usage();

        Assert::AreEqual(string("Usage: " + PROGRAM_NAME + " <-a aValue><-b bValue>\n\n-a  This is 'a' Value description\n-b  This is 'b' Value description\n[]  Argument is optional."), actual, L"The usage text did not match");
    }

    TEST_METHOD(Usage_Displays_WithOptionalOption) {
        ArgumentParser* test = ConstructTestObject();

        test->AddOption(new ArgumentOption(TEST_OPTION, "", TEST_OPTION_DESCRIPTION, false));

        string actual = test->Usage();

        Assert::AreEqual(string("Usage: " + PROGRAM_NAME + " [-a]\n\n-a  This is 'a' Value description\n[]  Argument is optional."), actual, L"The usage text did not match");
    }

private:

    ArgumentParser* ArgumentParserTests::ConstructTestObject() {
        return new ArgumentParser(PROGRAM_NAME);
    }

    ArgumentParser* ArgumentParserTests::ConstructTestObjectWithOptions() {
        // Return a pointer because the destruction should NOT be called since those options will be deallocated with it.

        ArgumentParser* result = new ArgumentParser(PROGRAM_NAME);
        bool required = true;

        result->AddOption(new ArgumentOption(TEST_OPTION, TEST_OPTION_VALUE_NAME, TEST_OPTION_DESCRIPTION, required));
        result->AddOption(new ArgumentOption(TEST_OPTION2, TEST_OPTION2_VALUE_NAME, TEST_OPTION2_DESCRIPTION, required));

        return result;
    }
    };
}
