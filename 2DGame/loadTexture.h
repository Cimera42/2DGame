#ifndef LOADTEXTURE_H_INCLUDED
#define LOADTEXTURE_H_INCLUDED

#include "openglBits.h"
#include <SOIL.h>
#include <iostream>
#include <vector>

GLuint load2DTexture(std::string, bool); ///Loads 2DTexture and returns GLuint ID
GLuint load2DTextureArray(std::vector<std::string>, int); ///Loads 2DTextureArray and returns GLuint ID

#endif // LOADTEXTURE_H_INCLUDED