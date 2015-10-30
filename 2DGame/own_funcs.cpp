#include "own_funcs.h"

//Convert radians to degrees
float toDeg(float in)
{
    return in * 180/3.1415;
}

//Convert degrees to radians
float toRad(float in)
{
    return in * 3.1415/180;
}

//Rotate vector around 0,0 by *angle* radians
glm::vec2 rotateVec2(glm::vec2 point, float angle)
{
    glm::vec2 rotated_point;
    rotated_point.x = point.x * cos(angle) - point.y * sin(angle);
    rotated_point.y = point.x * sin(angle) + point.y * cos(angle);
    return rotated_point;
}

//Square a float
float sq(float in)
{
    return in*in;
}

//Returns squared distance between two points
float distanceSq(glm::vec2 a, glm::vec2 b)
{
    return sq(a.x-b.x)+sq(a.y-b.y);
}

std::vector<std::string> splitBy(std::string inString, char splitCharacter)
{
    std::vector<std::string> words;

    std::string wordBuffer;
    for (int i = 0 ; i < inString.length(); i++)  // iterate over all characters in 'inString'
    {
        if(inString[i] == splitCharacter)  // if this character is the character we might be done reading a word from 'inString'
        {
            if(i == inString.length() || inString[i+1] != splitCharacter)  // next character is not the character, so we are done reading a word
            {
                words.push_back(wordBuffer);
    	        wordBuffer = "";
            }
        }
        else // not the character .. so append the character to 'word'
        {
           wordBuffer += inString[i];
        }
    }
    words.push_back(wordBuffer);
    return words;
}
