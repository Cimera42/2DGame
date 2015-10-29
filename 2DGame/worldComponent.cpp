#include "worldComponent.h"
#include <glm/gtx/transform.hpp>

#include "logger.h"
#include "typeConversion.h"

ComponentID WorldComponent::ID;

WorldComponent::WorldComponent(){vanityName = "World Component";}
WorldComponent::~WorldComponent(){}
WorldComponent* WorldComponent::construct(glm::vec2 inPosition, glm::vec2 inScale, float inRotation)
{
    position = inPosition;
    scale = inScale;
    rotation = inRotation;

    updateMatrix();

    return this;
}
WorldComponent* WorldComponent::construct(std::vector<std::string> inArgs)
{
    if(inArgs.size() == 5)
    {
        float pX = stringToFloat(inArgs[0]);
        float pY = stringToFloat(inArgs[1]);

        float sX = stringToFloat(inArgs[2]);
        float sY = stringToFloat(inArgs[3]);

        float rot = stringToFloat(inArgs[4]);

        if(pX != -9999 && pY != -9999 &&
           sX != -9999 && sY != -9999 &&
           rot != -9999)
        {
            glm::vec2 pos = glm::vec2(pX,pY);
            glm::vec2 sca = glm::vec2(sX,sY);

            this->construct(pos,sca,rot);
        }
        else
        {
            Logger() << "Invalid input to World Component creation" << std::endl;
        }
    }
    else
    {
        Logger() << "Invalid number of arguments to World Component creation" << std::endl;
    }

    return this;
}

void WorldComponent::updateMatrix()
{
    modelMatrix = glm::mat4();
    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0,0,1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, 1.0f));
}
