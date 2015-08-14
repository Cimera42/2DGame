#include "sceneStore.h"

SceneStore::SceneStore(std::string name)
{
    //load the actual scene
    File readFile;
    sceneBlock = readFile.readFromFile(name);
    if(readFile.success)
    {
        //Process the block into whatever format/create objects/whatever - later
        amountOfElements = sceneBlock->elements.size();
        correctlyLoaded = true;
    }
}
