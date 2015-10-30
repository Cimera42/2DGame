#ifndef OWN_FUNCS_H_INCLUDED
#define OWN_FUNCS_H_INCLUDED

#include <glm/glm.hpp>
#include <vector>
#include <string>

float toDeg(float in);
float toRad(float in);
glm::vec2 rotateVec2(glm::vec2 point, float angle);
float sq(float in);
float distanceSq(glm::vec2 a, glm::vec2 b);
std::vector<std::string> splitBy(std::string inString, char splitCharacter);

#endif // OWN_FUNCS_H_INCLUDED
