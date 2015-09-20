#include "mouseHandler.h"

MouseMoveData mouseData;
std::unordered_map<int, int> mouseButtonList;
extern unsigned short modList;
extern bool checkModifiers(unsigned short inMods, bool strict);

void mouseMoveInput(GLFWwindow* inWindow, double xPos, double yPos)
{
    MouseMoveData data;
    data.xScreenPos = xPos;
    data.yScreenPos = yPos;

    data.xScreenChange = xPos - mouseData.xScreenPos;
    data.yScreenChange = yPos - mouseData.yScreenPos;

    mouseData = data;
}

void mouseButtonInput(GLFWwindow* inWindow, int button, int action, int mods)
{
    mouseButtonList[button] = action;
}

bool isButtonPressed(int buttonCode)
{
    std::unordered_map<int, int>::iterator fi = mouseButtonList.find(buttonCode);
    if(fi != mouseButtonList.end())
    {
        if(fi->second == GLFW_PRESS || fi->second == GLFW_REPEAT)
        {
            return true;
        }
    }
    return false;
}

bool isButtonPressed(int buttonCode, int modifiers, bool strict)
{
    if(checkModifiers(modifiers, strict))
    {
        return isButtonPressed(buttonCode);
    }
    return false;
}
