#ifndef OPENGLBITS_H_INCLUDED
#define OPENGLBITS_H_INCLUDED

#define GLEW_STATIC
#include "glew.h"
#include <GLFW/glfw3.h>

///Same functions to replace default to prevent redundant calls
void glSetActiveTexture(GLenum);
void glSetBindTexture(GLenum, GLuint);
void glSetBindVertexArray(GLuint);
void glSetBindFramebuffer(GLenum, GLuint);
void glSetUseProgram(GLuint);

///Initialisation
void initGL();

#endif // OPENGLBITS_H_INCLUDED
