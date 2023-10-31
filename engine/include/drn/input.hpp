#ifndef DORIAN_INPUT
#define DORIAN_INPUT

#include "boolArray.hpp"

#define DORIAN_LUP 'w'
#define DORIAN_LDOWN 's'
#define DORIAN_LLEFT 'a'
#define DORIAN_LRIGHT 'd'
#define DORIAN_A 'j'
#define DORIAN_B 'k'
#define DORIAN_X 'u'
#define DORIAN_Y 'i'
#define DORIAN_START 27
#define DORIAN_SELECT 9

namespace drn {
    enum Input{LUp, LDown, LLeft, LRight, Start, Select, A, B, X, Y};
    extern BoolArray KeyboardInput;

    extern bool isUsingController[2];

    extern bool InputPressed(int i);
    extern bool InputReleased(int i);
    extern bool InputDown(int i);
}

#endif