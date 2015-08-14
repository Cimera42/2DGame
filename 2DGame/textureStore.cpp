#include "textureStore.h"

TextureStore::TextureStore(std::string name)
{
    //load the actual texture - todo

    //Read file
    File readFile;
    textureBlock = readFile.readFromFile(name);
    if(readFile.success)
    {
        //extract the element(s) from the file.
        for(int i; i < textureBlock->elements.size(); i++)
        {
            if(textureBlock->elements[i]->elementName == "Texture") //Checks that the element is a texture. Aka. ignore all non textures in file, which shouldnt exist anyway.
            {
                //HOW TO EXTRACT PROPERTIES SO THERE IS KINDA SOME FORM OF ERROR CHECKING + FASTISH
            }
        }
    }
    //possibly load a file containing texture parameters (via. load) and then use that datablock to load
    //a new texture with properties (srgb, height/widths/ mipmaps/ whatever).
    correctlyLoaded = true;
}
