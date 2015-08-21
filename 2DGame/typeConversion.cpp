#include "typeConversion.h"

#include <stdlib.h>
#include <sstream>
#include <cstring>

bool stringToBool(std::string s)
{
    if(s == "1" || s == "true")
        return true;
    return false;
}

int stringToInt(std::string s)
{
    int i;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail()) {
        // not an integer
        return -9999;
    }
    return i;
}

float stringToFloat(std::string s)
{
    float i;
    std::stringstream ss(s);
    ss >> i;
    if (ss.fail()) {
        // not a float
        return -9998;
    }
    return i;
}


//fix up
char* StrtoChar(std::string s)
{
   char *pc = new char[s.size()+1];
   std::strcpy(pc, s.c_str());
   return pc;
}

std::string InttoStr(int a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

