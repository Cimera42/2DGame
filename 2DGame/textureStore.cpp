#include "textureStore.h"
#include "loadTexture.h"

///TextureStore allows us to store the actual textures from files!
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
                        textureFile = textureBlock->getCurrentValue<std::string>();
                    else if(textureBlock->checkCurrentProperty("srgb"))
                        srgb = textureBlock->getCurrentValue<bool>();
                    else
                        std::cout<<"Innapropriate texture property in: "<<readFile.fileName<<std::endl;
                }
                if (textureFile != "") //After we've loaded all properties for the texture element, we can actually load the texture!...
                {
                    textureID = load2DTexture(textureFile, srgb); //Load the actual texture we store
                    if(textureID != 0)
                        correctlyLoaded = true;
                }
            }
        }
    }
}

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
