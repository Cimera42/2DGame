#ifndef TEXTURESTORE_H_INCLUDED
#define TEXTURESTORE_H_INCLUDED

#include "fileReader.h"
#include "store.h"
#include "openGLFunctions.h"
#include <pthread.h>

class TextureStore : public Store
{
public:
    TextureStore();
    ~TextureStore();
    void loadStore(std::string);

    //Extracted
    DataBlock* textureBlock;
    std::string textureFile;
    bool srgb;

    //Loaded
    GLuint textureID;

    pthread_mutex_t textureLoadMutex ;
};

#endif // TEXTURESTORE_H_INCLUDED
