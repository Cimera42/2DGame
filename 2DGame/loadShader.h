#ifndef LOADSHADER_H_INCLUDED
#define LOADSHADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <map>
#include <GL/glew.h>

//! \brief Loads a shader to display images on screen.
//! \param [in] vertPath A filepath of vertex shader
//! \param [in] fragPath A filepath of fragment shader
//! \param [in] layoutLocations A vector of the 'in' parameters for the shader. (Eg. "VertexPos")
//! \param [in] frameLocations A vector of the 'out' parameters for the shader. (Eg. "Colour")
GLuint loadShader(char *, char*, std::vector<const char*>);

//! \brief Loads a shader to display images on screen.
//! \param [in] vertPath A filepath of vertex shader
//! \param [in] fragPath A filepath of fragment shader
//! \param [in] geomPath A filepath of geometry shader
//! \param [in] layoutLocations A vector of the 'in' parameters for the shader. (Eg. "VertexPos")
//! \return GLuint ID for the shader. Can also be accessed through the global shaders[shaderName].
GLuint loadShaderG(char *, char*, char*, std::vector<const char*>);

GLuint deleteShader(GLuint);

#endif // LOADSHADER_H_INCLUDED
