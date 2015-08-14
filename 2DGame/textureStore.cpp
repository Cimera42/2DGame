#include "textureStore.h"
#include "loadTexture.h"

bool stringToBool(std::string const& s) {
    if(s == "1" || s == "true")
        return true;
    return false;
}

///TextureStore is an example to show how weird and difficult it may be to load file properties...
TextureStore::TextureStore(std::string name)
{
    //load the actual texture - todo

    //Read file
    File readFile;
    textureBlock = readFile.readFromFile(name);
    if(readFile.success)
    {
        //extract the element(s) from the file.
        for(int i = 0; i < textureBlock->elements.size(); i++)
        {
            if(textureBlock->elements[i]->elementName == "Texture") //Checks that the element is a texture. Aka. ignore all non textures in file, which shouldnt exist anyway.
            {
                //hate not being able to use the values immediately. basically the same issue as we had with loading...
                std::string textureFile = "";
                bool srgb = false;
                //HOW TO EXTRACT PROPERTIES SO THERE IS KINDA SOME FORM OF ERROR CHECKING + FASTISH
                for(int j = 0; j < textureBlock->elements[i]->properties.size(); j++)
                {
                    if(textureBlock->elements[i]->properties[j]->propertyName == "filename")
                    {
                        //Handle settings here rather than inside the loadTexture???
                        textureFile = textureBlock->elements[i]->properties[j]->values[0]; //assume only 1 data value??? or what.
                    }
                    else if(textureBlock->elements[i]->properties[j]->propertyName == "srgb")
                    {
                        srgb = stringToBool(textureBlock->elements[i]->properties[j]->values[0]); //convert to bool
                    }
                    else
                    {
                        std::cout<<"Innapropriate texture property in: "<<readFile.fileName<<std::endl;
                    }
                }
                if (textureFile != "") //After we've loaded all properties for the texture element, we can actually load the texture!...
                {
                    textureID = load2DTexture(textureFile, stringToBool);
                }
            }
            else
            {
                std::cout<<"Innapropriate texture element in: "<<readFile.fileName<<std::endl;
            }
        }
        correctlyLoaded = true;
    }

    //possibly load a file containing texture parameters (via. load) and then use that datablock to load
    //a new texture with properties (srgb, height/widths/ mipmaps/ whatever).
    //correctlyLoaded = true;
}
