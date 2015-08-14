#include "load&store.h"

#include <iostream>
std::map<std::string, BaseStore*> internalMap;

SceneStore::SceneStore(std::string name)
{
    //load the actual scene
    File readFile;
    sceneBlock = readFile.readFromFile(name);
    if(readFile.success)
    {
        //Process the block into whatever format/create objects/whatever
        amountOfElements = sceneBlock->elements.size();
        correctlyLoaded = true;
    }
}

TextureStore::TextureStore(std::string name)
{
    //load the actual texture
    correctlyLoaded = true;
}


