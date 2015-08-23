#include "textureStore.h"
#include "loadTexture.h"
#include "textureLoadSystem.h"
#include <pthread.h>

///TextureStore allows us to store the actual textures from files!
TextureStore::TextureStore()
{
    //This store deals with only extracting 1 texture from 1 file.
    /* TODO:
    - multiple textures - texturepackStore? - this will evoke many textureStores which can be used to preload data (or pass pointers around I guess)
    - fix this up to only contain 1 texture & make property loading less dodgy
    */

    //Default values
    textureID = 0;
    srgb = false;
    textureFile = "";
}

void TextureStore::loadStore(std::string name)
{
    //Read file
    File readFile;
    textureBlock = readFile.readFromFile(name);
    if(readFile.success)
    {
        if(textureBlock->getNextElement()) //Changed to if for only the one texture.
        {
            if(textureBlock->checkCurrentElement("Texture"))
            {
                while(textureBlock->getNextProperty())
                {
                    if(textureBlock->checkCurrentProperty("filename"))
                        textureFile = readFile.fileDirectory+textureBlock->getCurrentValue<std::string>();
                    else if(textureBlock->checkCurrentProperty("srgb"))
                        srgb = textureBlock->getCurrentValue<bool>();
                    else
                        std::cout<<"Innapropriate texture property in: "<<readFile.fileName<<std::endl;
                }
                if (textureFile != "") //After we've loaded all properties for the texture element, we can actually load the texture!...
                {
                    int width, height;
                    textureData = load2DTextureData(textureFile, &width, &height); //Load the actual texture we store

                    TextureToLoad toLoad;
                    toLoad.idLoc = &textureID;
                    toLoad.width = width;
                    toLoad.height = height;
                    toLoad.data = textureData;
                    toLoad.srgb = srgb;

                    //Mutex lock variable while editing
                    pthread_mutex_lock(&textureLoadMutex);
                    texturesToLoad.push_back(toLoad);
                    pthread_mutex_unlock(&textureLoadMutex);

                    if(textureData != 0)
                        correctlyLoaded = true;
                }
            }
        }
    }
}

