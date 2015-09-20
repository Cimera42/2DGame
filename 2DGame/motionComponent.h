#ifndef MOTIONCOMPONENT_H_INCLUDED
#define MOTIONCOMPONENT_H_INCLUDED

#include "component.h"
#include <glm/glm.hpp>

class MotionComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        MotionComponent(float);
        virtual ~MotionComponent();

        float slowRate;
        glm::vec2 velocity;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // MOTIONCOMPONENT_H_INCLUDED
