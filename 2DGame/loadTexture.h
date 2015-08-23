#ifndef LOADTEXTURE_H_INCLUDED
#define LOADTEXTURE_H_INCLUDED

#include "openGLFunctions.h"
#include <SOIL.h>
#include <iostream>
#include <vector>

GLuint load2DTexture(std::string, bool); ///Loads 2DTexture and returns GLuint ID
unsigned char* load2DTextureData(std::string, int*, int*); ///Loads 2DTexture and returns its data
GLuint load2DTextureByData(unsigned char*, int, int, bool); ///Loads 2DTexture by data and return GLuint ID
GLuint load2DTextureArray(std::vector<std::string>, int); ///Loads 2DTextureArray and returns GLuint ID

#endif // LOADTEXTURE_H_INCLUDED
