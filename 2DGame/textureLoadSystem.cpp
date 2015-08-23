#include "textureLoadSystem.h"
#include "loadTexture.h"
#include "globals.h"
#include <pthread.h>

pthread_mutex_t textureLoadMutex = PTHREAD_MUTEX_INITIALIZER;
std::vector<TextureToLoad> texturesToLoad;
SystemID TextureLoadSystem::ID;

TextureLoadSystem::TextureLoadSystem(){}
TextureLoadSystem::~TextureLoadSystem(){}

void TextureLoadSystem::update()
{
    int vecSize = texturesToLoad.size();
    if(vecSize > 0)
    {
        for(int i = 0; i < vecSize; i++)
        {
            TextureToLoad* texToLoad = &texturesToLoad[i];
            *texToLoad->idLoc = load2DTextureByData(texToLoad->data, texToLoad->width, texToLoad->height, texToLoad->srgb);
        }
        texturesToLoad.clear();
    }
}
