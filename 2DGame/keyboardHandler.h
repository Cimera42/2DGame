#ifndef KEYBOARDHANDLER_H_INCLUDED
#define KEYBOARDHANDLER_H_INCLUDED

#include <unordered_map>
#include <GLFW/glfw3.h>

extern std::unordered_map<int, int> keyList;
extern unsigned short modList;

void keyboardInput(GLFWwindow* inWindow, int keyCode, int scanCode, int action, int modifiers);
bool checkModifiers(unsigned short inMods, bool strict);
bool isKeyPressed(int keyCode);
bool isKeyPressed(int keyCode, int modifiers, bool strict);

#endif // KEYBOARDHANDLER_H_INCLUDED
