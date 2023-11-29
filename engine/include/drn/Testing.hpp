#ifndef DORIAN_TESTING
#define DORIAN_TESTING

#include <iostream>
#include <vector>

namespace drn {
    class TestBase {
        public:

        virtual int RunTest();
    };

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
            std::cout << m_text << "\n";
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
                std::cout << "Test Successful\n";
                return 0;
            } else {
                std::cout << "Test failed. Returned \"" << Result << "\". Expected \"" << m_ExpectedResult << "\"\n";
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

    std::cout << "\nSuccessful Tests: " << (Tests - Errors) << "\nFailed Tests: " << Errors << "\n";

    return Errors;
}

#endif