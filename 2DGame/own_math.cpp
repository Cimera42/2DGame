#include "own_math.h"

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
