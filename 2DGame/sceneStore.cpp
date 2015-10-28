#include "sceneStore.h"

#include "openGLFunctions.h"
#include "entity.h"
#include "globals.h"
#include "main.h"
#include "windowComponent.h"
#include "render2DComponent.h"
#include "worldComponent.h"
#include "terrainComponent.h"
#include "tempplayerControlComponent.h"
#include "cameraComponent.h"
#include "motionComponent.h"
#include "colliderComponent.h"
#include "playerComponent.h"
#include "logger.h"
/**SceneStore allows us to store the entities and any global properties.
    - Evokes components on entities. Essentially the only reason this is a store is to allow for preloading of levels in the future.
**/
SceneStore::SceneStore()
{

}

void SceneStore::loadStore(std::string name)
{
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    GLFWwindow* tempWindow = glfwCreateWindow(1,1,"",NULL,glContext);
    glfwMakeContextCurrent(tempWindow);
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
                        /*std::string filename = readFile.fileDirectory+sceneBlock->getCurrentValue<std::string>(0);
                        WindowComponent* win = new WindowComponent(filename);
                        //Temporary system init???? WHERE TO PUT
                        ent->addComponent(win);*/
                    }
                    else if(sceneBlock->checkCurrentProperty("render2d"))
                    {
                        //Render2D component FOR NOW
                        glm::vec4 uvs = sceneBlock->getCurrentValue<glm::vec4>(0);
                        Render2DComponent* render = new Render2DComponent(glm::vec2(uvs.x,uvs.y), glm::vec2(uvs.z,uvs.w));
                        ent->addComponent(render);
                    }
                    else if(sceneBlock->checkCurrentProperty("world"))
                    {
                        //World component FOR NOW
                        WorldComponent* world = new WorldComponent(sceneBlock->getCurrentValue<glm::vec2>(0),sceneBlock->getCurrentValue<glm::vec2>(2),sceneBlock->getCurrentValue<float>(4));
                        ent->addComponent(world);
                    }
                    else if(sceneBlock->checkCurrentProperty("player"))
                    {
                        //Player component FOR NOW
                        PlayerComponent* player = new PlayerComponent(sceneBlock->getCurrentValue<int>(0));
                        ent->addComponent(player);
                    }
                    else if(sceneBlock->checkCurrentProperty("motion"))
                    {
                        //Motion component FOR NOW
                        MotionComponent* motion = new MotionComponent(sceneBlock->getCurrentValue<float>(0),sceneBlock->getCurrentValue<float>(1));
                        ent->addComponent(motion);
                    }
                    else if(sceneBlock->checkCurrentProperty("terrain"))
                    {
                        //Terrain component FOR NOW
                        int numPoints = sceneBlock->getCurrentValue<int>(0);
                        float heightScale = sceneBlock->getCurrentValue<float>(1);
                        float noiseScale = sceneBlock->getCurrentValue<float>(2);
                        float baseline = sceneBlock->getCurrentValue<float>(3);
                        TerrainComponent* terrain = new TerrainComponent(numPoints, heightScale, noiseScale, baseline);
                        ent->addComponent(terrain);
                    }
                    else if(sceneBlock->checkCurrentProperty("camera"))
                    {
                        float zoom = sceneBlock->getCurrentValue<float>(0);
                        bool active = sceneBlock->getCurrentValue<bool>(1);
                        //Camera component FOR NOW
                        CameraComponent* camera = new CameraComponent(zoom, active);
                        ent->addComponent(camera);
                    }
                    else if(sceneBlock->checkCurrentProperty("collider"))
                    {
                        std::string type = sceneBlock->getCurrentValue<std::string>(0);
                        std::string collisionType = sceneBlock->getCurrentValue<std::string>(1);
                        glm::vec2 posOffset = sceneBlock->getCurrentValue<glm::vec2>(2);
                        float width = sceneBlock->getCurrentValue<float>(4);
                        float height = sceneBlock->getCurrentValue<float>(5);
                        //Collider component FOR NOW
                        ColliderComponent* collider = new ColliderComponent(type, collisionType, posOffset, width, height);
                        ent->addComponent(collider);
                    }
                    else if(sceneBlock->checkCurrentProperty("control"))
                    {
                        float speed = sceneBlock->getCurrentValue<float>(0);
                        int up = sceneBlock->getCurrentValue<char>(1);
                        int down = sceneBlock->getCurrentValue<char>(2);
                        int left = sceneBlock->getCurrentValue<char>(3);
                        int right = sceneBlock->getCurrentValue<char>(4);
                        //Player control component FOR NOW
                        PlayerControlComponent* control = new PlayerControlComponent(speed, up, down, left, right);
                        ent->addComponent(control);
                    }
                    else
                    {
                        Logger()<<"Innapropriate scene property in: "<<readFile.fileName<<std::endl;
                    }
                }
            }
        }
        correctlyLoaded = true;
    }
    glfwDestroyWindow(tempWindow);
}
