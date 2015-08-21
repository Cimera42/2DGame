#ifndef WINDOWCOMPONENT_H_INCLUDED
#define WINDOWCOMPONENT_H_INCLUDED

#include <string>
#include "component.h"
#include "fileReader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class WindowComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        WindowComponent(std::string fileName);
        virtual ~WindowComponent();

        //Values set
        std::string windowTitle;
        glm::vec2 windowSize;
        bool modeWindowed = true;
        bool modeFullscreen = false;
        bool modeBorderless = false;

        //Values generated
        float windowAspect;
        int clientWidth, clientHeight;
        GLFWwindow* glfwWindow;
        GLFWmonitor* glfwMonitor;
        const GLFWvidmode* glfwVideoMode;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

void windowCloseEvent(GLFWwindow*);

#endif // WINDOWCOMPONENT_H_INCLUDED