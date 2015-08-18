#ifndef WORLDCOMPONENT_H_INCLUDED
#define WORLDCOMPONENT_H_INCLUDED

#include "component.h"
#include <glm/glm.hpp>

class WorldComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        WorldComponent(glm::vec2);
        virtual ~WorldComponent();

        glm::vec2 position;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // WORLDCOMPONENT_H_INCLUDED
