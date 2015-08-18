#ifndef WINDOWCOMPONENT_H_INCLUDED
#define WINDOWCOMPONENT_H_INCLUDED

#include "component.h"
#include <GLFW/glfw3.h>

class WindowComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        WindowComponent(char*, int, int);
        virtual ~WindowComponent();

        //Values set
        char* windowTitle;
        int windowWidth, windowHeight;

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
