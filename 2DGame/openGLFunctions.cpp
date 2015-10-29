#include "openGLFunctions.h"
#include <iostream>
#include <stdlib.h>
#include "windowComponent.h"
#include "logger.h"

GLenum currentState;
void glSetActiveTexture(GLenum state) //Handler to stop redundant glActiveTexture calls, hopefully speed up frames.
{
    if (state != currentState)
    {
        glActiveTexture(state);
        currentState = state;
    }
}

GLuint currentTexture;
void glSetBindTexture(GLenum target, GLuint texture)
{
    if(texture != currentTexture)
    {
        //Stops redundant texture calls.
        glBindTexture(target, texture);
        currentTexture = texture;
    }
}

GLuint currentVertexArray;
void glSetBindVertexArray(GLuint vertexArray)
{
    if(vertexArray != currentVertexArray)
    {
        //Stops redundant vertex bind calls.
        glBindVertexArray(vertexArray);
        currentVertexArray = vertexArray;
    }
}

GLuint currentFramebuffer[3]; //0 is GL_DRAW_FRAMEBUFFER, 1 GL_READ_FRAMEBUFFER, 2 GL_FRAMEBUFFER;
void glSetBindFramebuffer(GLenum target, GLuint framebuffer)
{
    int index; //Not the most efficient system but eh
    if (target == GL_DRAW_FRAMEBUFFER)
        index = 0;
    else if (target == GL_READ_FRAMEBUFFER)
        index = 1;
    else if (target == GL_FRAMEBUFFER)
        index = 2;
    if(framebuffer != currentFramebuffer[index])
    {
        //Stops redundant framebuffer calls.
        glBindFramebuffer(target, framebuffer);
        currentFramebuffer[index] = framebuffer;
    }
}

GLuint currentProgram;
void glSetUseProgram(GLuint program) //Handler to stop redundant glUseProgram calls.
{
    if (program != currentProgram)
    {
        glUseProgram(program);
        currentProgram = program;
    }
}

void errCallback(int inCode, const char* descrip)
{
    Logger() << "#GLFW ERROR# -- " << descrip << std::endl;
}

GLFWwindow* glContext;
WindowComponent* mainWindow;
bool initGLFW()
{
    if(!glfwInit())
    {
        Logger() << "GLFW init failed" << std::endl;
        return false;
    }
    else
    {
        Logger() << "GLFW init successful" << std::endl;
    }
    glfwSetErrorCallback(errCallback);

    //Load main context for sharing
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glContext = glfwCreateWindow(1,1,"CONTEXT",NULL,NULL);

    //Load display window
    //Possibly could be turned back into an entity
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    mainWindow = (new WindowComponent())->construct("debug/window.cfg",glContext);
    glfwMakeContextCurrent(mainWindow->glfwWindow);

    return true;
}

bool initGLEW()
{
    glewExperimental = true;
    GLenum err = glewInit();
    if(err!=GLEW_OK)
    {
        Logger()<<"GLEW failed to load"<<std::endl;
        return false;
    }
    else
    {
        Logger()<<"GLEW loaded"<<std::endl;
        Logger() << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        //Sets up common OpenGL Functions
        //glEnable(GL_MULTISAMPLE);
        //glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);
        //glEnable(GL_PROGRAM_POINT_SIZE);
        //glEnable(GL_LINE_SMOOTH);
        //glLineWidth(1);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    return true;
}
