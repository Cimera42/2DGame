#ifndef TEXTURESTORE_H_INCLUDED
#define TEXTURESTORE_H_INCLUDED

#include "fileReader.h"
#include "store.h"
#include "openGLFunctions.h"

class TextureStore : public Store
{
public:
    TextureStore(std::string);
    ~TextureStore(){};

    DataBlock* textureBlock;
    GLuint textureID;
};

#endif // TEXTURESTORE_H_INCLUDED
