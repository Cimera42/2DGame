#ifndef MOUSEHANDLER_H_INCLUDED
#define MOUSEHANDLER_H_INCLUDED

#include <unordered_map>
#include <GLFW/glfw3.h>

struct MouseMoveData
{
    bool processed = false;

    double xScreenPos = 0, yScreenPos = 0;
    double xScreenChange = 0, yScreenChange = 0;

    double xScreenCoord = 0, yScreenCoord = 0;
    double xScreenCoordChange = 0, yScreenCoordChange = 0;

    double xWorldCoord = 0, yWorldCoord = 0;
    double xWorldCoordChange = 0, yWorldCoordChange = 0;
};
extern MouseMoveData mouseData;

extern std::unordered_map<int, int> mouseButtonList;

void mouseMoveInput(GLFWwindow*, double xPos, double yPos);
void mouseButtonInput(GLFWwindow* inWindow, int button, int action, int mods);

bool isButtonPressed(int buttonCode);
bool isButtonPressed(int buttonCode, int modifiers, bool strict);

#endif // MOUSEHANDLER_H_INCLUDED
