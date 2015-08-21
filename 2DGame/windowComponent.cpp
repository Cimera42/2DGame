#include "windowComponent.h"
#include "globals.h"
#include <iostream>

ComponentID WindowComponent::ID;

WindowComponent::WindowComponent(std::string fileName)
{
    //load the the window from file. Most components should not have this form of reading directly.
    File readFile;
    DataBlock* windowBlock = readFile.readFromFile(fileName);
    if(readFile.success)
    {
        //process this block
        while(windowBlock->getNextElement())//check all properties for window
        {
            if(windowBlock->checkCurrentElement("Window"))
            {
                while(windowBlock->getNextProperty()) //Add the components to the entity
                {
                    if(windowBlock->checkCurrentProperty("title"))
                        windowTitle = windowBlock->getCurrentValue<std::string>();
                    else if(windowBlock->checkCurrentProperty("size"))
                        windowSize = windowBlock->getCurrentValue<glm::vec2>();
                    else if(windowBlock->checkCurrentProperty("windowed"))
                        modeWindowed = windowBlock->getCurrentValue<bool>();
                    else if(windowBlock->checkCurrentProperty("fullscreen"))
                        modeFullscreen = windowBlock->getCurrentValue<bool>();
                    else if(windowBlock->checkCurrentProperty("borderless"))
                        modeBorderless = windowBlock->getCurrentValue<bool>();
                    else
                        std::cout<<"Innapropriate window property in: "<<readFile.fileName<<std::endl;
                }
            }
        }
    }
    //char* inTitle, int inWindowWidth, int inWindowHeight
    if(!glfwInit())
    {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return;
    }
    else
    {
        std::cout << "Initialised GLFW" << std::endl;
    }

    windowAspect = windowSize.x/windowSize.y;

    glfwMonitor = glfwGetPrimaryMonitor();
    glfwVideoMode = glfwGetVideoMode(glfwMonitor);
    clientWidth = glfwVideoMode->width;
    clientHeight = glfwVideoMode->height;
    glfwWindowHint(GLFW_RED_BITS, glfwVideoMode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, glfwVideoMode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, glfwVideoMode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, glfwVideoMode->refreshRate);
    if (modeFullscreen)
    {
        glfwWindow = glfwCreateWindow(windowSize.x,windowSize.y, windowTitle.c_str(), glfwMonitor, NULL);
    }
    else if(modeBorderless)
    {
        glfwWindowHint(GLFW_DECORATED, GL_FALSE);

        glfwWindow = glfwCreateWindow(windowSize.x,windowSize.y, windowTitle.c_str(), NULL, NULL);
        glfwSetWindowPos(glfwWindow, clientWidth/2-windowSize.x/2, clientHeight/2-windowSize.y/2);
    }
    else if(modeWindowed)
    {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindow = glfwCreateWindow(windowSize.x,windowSize.y, windowTitle.c_str(), NULL, NULL);
        glfwSetWindowPos(glfwWindow, clientWidth/2-windowSize.x/2, clientHeight/2-windowSize.y/2);
    }

    if(!glfwWindow)
    {
        std::cout << "Failed to create window" << std::endl;
        return;
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
