#include "windowComponent.h"
#include "globals.h"
#include <iostream>

ComponentID WindowComponent::ID;

WindowComponent::WindowComponent(char* inTitle, int inWindowWidth, int inWindowHeight)
{
    if(!glfwInit())
    {
        std::cout << "Failed to initialise GLFW" << std::endl;
    }
    else
    {
        std::cout << "Initialised GLFW" << std::endl;
    }

    windowWidth = inWindowWidth;
    windowHeight = inWindowHeight;
    windowAspect = windowWidth/windowHeight;
    windowTitle = inTitle;

    glfwMonitor = glfwGetPrimaryMonitor();
    glfwVideoMode = glfwGetVideoMode(glfwMonitor);
    clientWidth = glfwVideoMode->width;
    clientHeight = glfwVideoMode->height;

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindow = glfwCreateWindow(windowWidth,windowHeight, inTitle, NULL, NULL);
    glfwSetWindowPos(glfwWindow, clientWidth/2-windowWidth/2, clientHeight/2-windowHeight/2);

    if(!glfwWindow)
    {
        std::cout << "Failed to create window" << std::endl;
    }
    else
    {
        glfwMakeContextCurrent(glfwWindow);
        glfwWindow = glfwGetCurrentContext();

        glfwSetWindowCloseCallback(glfwWindow, windowCloseEvent);
    }
}
WindowComponent::~WindowComponent()
{
    glfwDestroyWindow(glfwWindow);
    std::cout << "Window destroyed" << std::endl;
}

void windowCloseEvent(GLFWwindow* closingWindow)
{
    shouldExit = true;
}
