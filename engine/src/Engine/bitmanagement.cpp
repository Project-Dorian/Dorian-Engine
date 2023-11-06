#include <drn/boolArray.hpp>
#include <stdexcept>
#include <cstring>
//#include <iostream>

using namespace drn;

BoolArray::BoolArray(unsigned char size) {
    if (size < 1) {
        throw std::runtime_error("drn::BoolArray must have an address size of 1 or greater");
    }
    m_size = size;

    m_bitData = new char[size+1];
    m_bitData[size] = '\0';

    for(unsigned long long i=0; i<size; i++) 
        m_bitData[i] = 0;
}

BoolArray::~BoolArray() {
    //delete m_bitData;
}

BoolArray BoolArray::operator=(std::string data) {
    if (data.length() == m_size) {
        strcpy(m_bitData, data.c_str());
    } else {
        int i = -1;

        while (++i <= data.length()) {
            if (data[data.length()-i]-48) { // Calculation should be either 1 or 0
                this->on((i));
            } else {
                this->off((i));
            }
        }

        while (!(i % 8)) this->off(i++);
    }

    return *this;
}

bool BoolArray::operator[](unsigned long long i) {
    return m_bitData[i/8] & (1 << i%8);
}

char* BoolArray::binary() {
    char* m_PreviouslyReadBinaryString = new char[m_size*8+1];
    m_PreviouslyReadBinaryString[m_size*8] = '\0';

    for (int i{0}; i < m_size*8; i++) {
        m_PreviouslyReadBinaryString[i] = this->operator[](m_size*8-1-i)+48;
    }
    return m_PreviouslyReadBinaryString;
}

char* BoolArray::ascii() {
    return (char*)m_bitData;
}

bool BoolArray::on(unsigned long long i) {
    m_bitData[i/8] = m_bitData[i/8] | (1 << i%8);
    return true;
}

bool BoolArray::off(unsigned long long i) {
    m_bitData[i/8] = m_bitData[i/8] & ~(1 << i%8);
    return false;
}