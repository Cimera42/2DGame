#include "openglBits.h"
#include <iostream>

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

void initGL()
{
    glewExperimental = true;
    GLenum err = glewInit();
    if(err!=GLEW_OK)
    {
        std::cout<<"GLEW failed to load"<<std::endl;
    }
    std::cout << "OpenGL " << glGetString(GL_VERSION) << ", GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    //Sets up common OpenGL Functions
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    //glEnable(GL_LINE_SMOOTH);
    glLineWidth(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*glShadeModel(GL_FLAT);
    glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);*/
}
