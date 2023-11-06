#ifndef DORIAN_BIT
#define DORIAN_BIT

#include <string>

namespace drn {
    // An array in groups of 8 bits. I would permit use of irregular number of bits, but this is not structured to do so
    class BoolArray {
        private:
        char* m_bitData;
        unsigned char m_size;

        public:
        BoolArray(unsigned char size);
        ~BoolArray();

        // Allows you to assign a binary string or raw data to the BoolArray
        // Example Usages:
        // drn::BoolArray ExampleBoolArray(1);
        // ExampleBoolArray = "01000101";
        // ExampleBoolArray = "E";
        BoolArray operator=(std::string data);

        // returns in boolean form the index
        bool operator[](unsigned long long i);

        // Outputs the information stored as a binary string
        char* binary();
        
        // outputs the information stored as a raw data string
        char* ascii();
        
        // Outputs the information stored as a hexidecimal
        char* hex();

        // Assigns 1 at the index
        bool on(unsigned long long i);
        // Assigns 0 at the index
        bool off(unsigned long long i);
    };

    typedef BoolArray BitArray;
}

#endif
