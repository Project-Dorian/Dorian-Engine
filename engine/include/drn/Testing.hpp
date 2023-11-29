#ifndef DORIAN_TESTING
#define DORIAN_TESTING

#include <iostream>
#include <vector>

namespace drn {
    // The Base Class for tests. Allows me to push back a Test<T> into TestsVector.
    class TestBase {
        public:

        virtual int RunTest();
    };

    // do not modify directly
    // loads all the tests into the unit test, and runs each test line by line.
    std::vector<TestBase*> TestsVector;

    class TestLabel : public TestBase {
        std::string m_text;
        public:

        using TestBase::TestBase;

        TestLabel(std::string s) {
            m_text = s;

            drn::TestsVector.push_back(this);
        }

        int RunTest() {
            std::cout << "\n" << m_text << "\n";
            return 2; 
        }
    };

    template <class T>
    class Test : public TestBase {
        private:
        T (*TestFunction)();
        T m_ExpectedResult;

        std::string m_TestName;
        public:
        Test(std::string TestName, T test(), T expectedResult) {
            drn::TestsVector.push_back(this);

            m_TestName = TestName;
            TestFunction = test;
            m_ExpectedResult = expectedResult;
        };

        int RunTest() {
            std::cout << m_TestName << ": ";
            T Result = (*TestFunction)();
            if (Result == m_ExpectedResult) {
                std::cout << "\x1B[1;32mTest Successful\x1b[0m\n";
                return 0;
            } else {
                std::cout << "\x1b[1;31mTest failed. Returned \"" << Result << "\". Expected \"" << m_ExpectedResult << "\"\x1b[0m\n";
                return 1;
            }
        }
    };

    extern std::string TestFileName;

};

int main() {
    int Errors = 0;
    int Tests = 0;
    
    std::cout << "Running Test: " << drn::TestFileName << "\n";

    for (drn::TestBase* t : drn::TestsVector) {
        int Response = t->RunTest();
        if (Response != 2) {
            Tests++;
            if (Response) Errors++;
        }
    };

    std::cout << "\x1B[1;32m\nSuccessful Tests: " << (Tests - Errors) << "\n\x1b[1;31mFailed Tests: " << Errors << "\x1b[0m\n";

    return Errors;
}

#endif