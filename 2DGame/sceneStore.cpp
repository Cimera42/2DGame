#include "sceneStore.h"

#include "openGLFunctions.h"
#include "entity.h"
#include "globals.h"
#include "main.h"
#include "windowComponent.h"
#include "render2DComponent.h"
#include "worldComponent.h"
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
                        //Window component
                        /*std::string filename = readFile.fileDirectory+sceneBlock->getCurrentValue<std::string>();
                        WindowComponent* win = new WindowComponent(filename);
                        //Temporary system init???? WHERE TO PUT
                        ent->addComponent(win);*/
                    }
                    else if(sceneBlock->checkCurrentProperty("render2d"))
                    {
                        //Render2D component FOR NOW
                        glm::vec2 heightWidth = sceneBlock->getCurrentValue<glm::vec2>(); //get the 2 float parameters in one FOR NOW
                        Render2DComponent* render = new Render2DComponent(heightWidth.x, heightWidth.y);
                        ent->addComponent(render);
                    }
                    else if(sceneBlock->checkCurrentProperty("world"))
                    {
                        //World component FOR NOW
                        WorldComponent* world = new WorldComponent(sceneBlock->getCurrentValue<glm::vec2>());
                        ent->addComponent(world);
                    }
                    else
                    {
                        std::cout<<"Innapropriate scene property in: "<<readFile.fileName<<std::endl;
                    }
                }
            }
        }
        correctlyLoaded = true;
    }
}
