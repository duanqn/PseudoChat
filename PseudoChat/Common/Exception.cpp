#include "Exception.h"

const char* PseudoChat::Exception::what(){
    return m_msg.c_str();
}