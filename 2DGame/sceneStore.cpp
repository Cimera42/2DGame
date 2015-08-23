#include "sceneStore.h"

#include "openGLFunctions.h"
#include "entity.h"
#include "globals.h"
#include "main.h"
#include "windowComponent.h"
/**SceneStore allows us to store the entities and any global properties.
    - Evokes components on entities. Essentially the only reason this is a store is to allow for preloading of levels in the future.
**/
SceneStore::SceneStore()
{

}

void SceneStore::loadStore(std::string name)
{
    //load the actual scene
    File readFile;
    sceneBlock = readFile.readFromFile(name);
    if(readFile.success)
    {
        //process this block
        while(sceneBlock->getNextElement()) //Changed to if for only the one texture.
        {
            if(sceneBlock->checkCurrentElement("Entity"))
            {
                Entity * ent = new Entity(); //Create the new entity from file
                addEntity(ent);
                while(sceneBlock->getNextProperty()) //Add the components to the entity
                {
                    if(sceneBlock->checkCurrentProperty("window"))
                    {
                    }
                    else if(sceneBlock->checkCurrentProperty("render2d"))
                        bool null = sceneBlock->getCurrentValue<bool>();
                    else
                    {
                        std::cout << sceneBlock->getCurrentValue<std::string>() << std::endl;
                        std::cout<<"Innapropriate scene property in: "<<readFile.fileName<<std::endl;
                    }

                }
            }
        }
        correctlyLoaded = true;
    }
}
