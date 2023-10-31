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
        BoolArray operator=(std::string data); // Allows you to assign a binary string to the BoolArray

        bool operator[](unsigned long long i); // Gets a copy of the index
        char* binary(); // Outputs the whole binary as a string
        char* ascii(); // outputs the binary as raw data

        bool on(unsigned long long i);
        bool off(unsigned long long i);
    };

    typedef BoolArray BitArray;
}

#endif
