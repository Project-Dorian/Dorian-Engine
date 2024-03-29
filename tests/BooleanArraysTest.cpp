#include <iostream>
#include <drn/boolArray.hpp>

using namespace std;
using namespace drn;

int main() {
    bool a{true};

    std::string testString = " ";
    testString[0] = 0b01000101;

    BoolArray testBools(1);
    testBools = testString;

    cout
        << "Reading the Binary: " << testBools.binary()
        << "\nReading the Ascii: " << testBools.ascii()
        << "\nAssigning 1 in index 2: " << testBools.on(2)
        << "\nAssigning 1 to index 3: " << testBools.on(3)
        << "\nReading Index 3: " << testBools[3]
        << "\nReading Index 2: " << testBools[2]
        << "\nReading the Binary: " << testBools.binary()
        << "\nReading the Ascii: " << testBools.ascii()
        << endl;

    return 0;
}