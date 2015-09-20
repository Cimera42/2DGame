#include "keyboardHandler.h"

std::unordered_map<int, int> keyList;
unsigned short modList;

void keyboardInput(GLFWwindow* inWindow, int keyCode, int scanCode, int action, int modifiers)
{
    keyList[keyCode] = action;
    modList = modifiers;
}

bool checkModifiers(unsigned short inMods, bool strict)
{
    if(strict)
    {
        return modList == inMods;
    }
    else
    {
        return modList & inMods == inMods;
    }
}

bool isKeyPressed(int keyCode)
{
    std::unordered_map<int, int>::iterator fi = keyList.find(keyCode);
    if(fi != keyList.end())
    {
        if(fi->second == GLFW_PRESS || fi->second == GLFW_REPEAT)
        {
            return true;
        }
    }
    return false;
}

bool isKeyPressed(int keyCode, int modifiers, bool strict)
{
    if(checkModifiers(modifiers, strict))
    {
        return isKeyPressed(keyCode);
    }
    return false;
}
