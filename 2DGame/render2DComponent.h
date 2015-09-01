#ifndef RENDER2DCOMPONENT_H_INCLUDED
#define RENDER2DCOMPONENT_H_INCLUDED

#include "component.h"
#include <glm/glm.hpp>

class Render2DComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        Render2DComponent(glm::vec2, glm::vec2);
        virtual ~Render2DComponent();

        glm::vec2 topLeftUV;
        glm::vec2 topRightUV;
        glm::vec2 bottomLeftUV;
        glm::vec2 bottomRightUV;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // RENDER2DCOMPONENT_H_INCLUDED
