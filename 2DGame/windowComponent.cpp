#include "windowComponent.h"
#include "globals.h"
#include "openGLFunctions.h"
#include "keyboardHandler.h"
#include "mouseHandler.h"
#include "logger.h"

ComponentID WindowComponent::ID;

WindowComponent::WindowComponent(){vanityName = "Window Component";}
WindowComponent::~WindowComponent()
{
    glfwDestroyWindow(glfwWindow);
    Logger() << "Window destroyed" << std::endl;
}
WindowComponent* WindowComponent::construct(std::string fileName, GLFWwindow* shareContext)
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
                        windowTitle = windowBlock->getCurrentValue<std::string>(0);
                    else if(windowBlock->checkCurrentProperty("size"))
                        windowSize = windowBlock->getCurrentValue<glm::vec2>(0);
                    else if(windowBlock->checkCurrentProperty("windowed"))
                        modeWindowed = windowBlock->getCurrentValue<bool>(0);
                    else if(windowBlock->checkCurrentProperty("fullscreen"))
                        modeFullscreen = windowBlock->getCurrentValue<bool>(0);
                    else if(windowBlock->checkCurrentProperty("borderless"))
                        modeBorderless = windowBlock->getCurrentValue<bool>(0);
                    else
                        Logger()<<"Innapropriate window property in: "<<readFile.fileName<<std::endl;
                }
            }
        }
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
        glfwWindow = glfwCreateWindow(windowSize.x,windowSize.y, windowTitle.c_str(), glfwMonitor, shareContext);
    }
    else if(modeBorderless)
    {
        glfwWindowHint(GLFW_DECORATED, GL_FALSE);

        glfwWindow = glfwCreateWindow(windowSize.x,windowSize.y, windowTitle.c_str(), NULL, shareContext);
        glfwSetWindowPos(glfwWindow, clientWidth/2-windowSize.x/2, clientHeight/2-windowSize.y/2);
    }
    else if(modeWindowed)
    {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindow = glfwCreateWindow(windowSize.x,windowSize.y, windowTitle.c_str(), NULL, shareContext);
        glfwSetWindowPos(glfwWindow, clientWidth/2-windowSize.x/2, clientHeight/2-windowSize.y/2);
    }
    if(!glfwWindow)
    {
        Logger() << "Failed to create window" << std::endl;
        return this;
    }
    else
    {
        glfwSetWindowCloseCallback(glfwWindow, windowCloseEvent);
        glfwSetKeyCallback(glfwWindow, keyboardInput);
        glfwSetCursorPosCallback(glfwWindow, mouseMoveInput);
        glfwSetMouseButtonCallback(glfwWindow, mouseButtonInput);
    }

    return this;
}
WindowComponent* WindowComponent::construct(std::vector<std::string> inArgs)
{
    return this;
}

void windowCloseEvent(GLFWwindow* closingWindow)
{
    shouldExit = true;
}
