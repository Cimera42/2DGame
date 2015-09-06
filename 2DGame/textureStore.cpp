#include "textureStore.h"
#include "loadTexture.h"
#include "logger.h"

///TextureStore allows us to store the actual textures from files!
TextureStore::TextureStore()
{
    //This store deals with only extracting 1 texture from 1 file.
    /* TODO:
    - multiple textures - texturepackStore? - this will evoke many textureStores which can be used to preload data (or pass pointers around I guess)
    - fix this up to only contain 1 texture & make property loading less dodgy
    */

    //Default values
    textureLoadMutex = PTHREAD_MUTEX_INITIALIZER;
    textureID = 0;
    srgb = false;
    textureFile = "";
}

TextureStore::~TextureStore()
{
    glDeleteTextures(1, &textureID);
}

void TextureStore::loadStore(std::string name)
{
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    GLFWwindow* tempWindow = glfwCreateWindow(1,1,"",NULL,glContext);
    glfwMakeContextCurrent(tempWindow);

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
                        textureFile = readFile.fileDirectory+textureBlock->getCurrentValue<std::string>(0);
                    else if(textureBlock->checkCurrentProperty("srgb"))
                        srgb = textureBlock->getCurrentValue<bool>(0);
                    else
                        Logger()<<"Innapropriate texture property in: "<<readFile.fileName<<std::endl;
                }
                if (textureFile != "") //After we've loaded all properties for the texture element, we can actually load the texture!...
                {
                    int tempID = load2DTexture(textureFile, srgb); //Load the actual texture we store
                    if(tempID != 0)
                    {
                        pthread_mutex_lock(&textureLoadMutex);
                        textureID = tempID;
                        pthread_mutex_unlock(&textureLoadMutex);

                        correctlyLoaded = true;
                    }
                }
            }
        }
    }
    glfwDestroyWindow(tempWindow);
}
