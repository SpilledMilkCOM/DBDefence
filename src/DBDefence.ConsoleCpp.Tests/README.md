# 🧪 DbDefence.ConsoleCpp.Tests ✅

 * Adjust include file path to point to project(s) you are testing.
 * Add reference to static libarary project (.lib)
 * Build and Run tests
 * Analyze Code Coverage
   * Check "{} Global Classes" for ArgumentOption and ArgumentParser
 
## 🤔 Things I Learned 🧠

* How to set up C++ unit tests in Visual Studio.
* Using Assert is pretty much the same.
* Enabling Code Coverage requires a non-default compile option.
  * **Project Properties - Linker** `Generate Debug Information optimized for sharing and publishing (/DEBUG:FULL)`
* Anonymous delegates (λ) take a [capture] in order to utilize local variables (where C# does not)

## 📚 REF 📓:

* [C++ Lambda (λ) Functions](https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-160)
* [Trouble Shooting Code Coverage](https://docs.microsoft.com/en-us/visualstudio/test/troubleshooting-code-coverage?view=vs-2019)