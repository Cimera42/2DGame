#ifndef MOTIONCOMPONENT_H_INCLUDED
#define MOTIONCOMPONENT_H_INCLUDED

#include "component.h"
#include <glm/glm.hpp>

class MotionComponent : public Component //Rename to physicsComponent
{
    private:
        static ComponentID ID;

    public:
        MotionComponent();
        virtual ~MotionComponent();
        MotionComponent* construct(float,float);
        MotionComponent* construct(std::vector<std::string>);
        MotionComponent* clone() {return new MotionComponent(*this);}

        float mass;
        float drag;
        //float friction;

        glm::vec2 acceleration;
        glm::vec2 velocity;

        void impulse(glm::vec2 in);

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // MOTIONCOMPONENT_H_INCLUDED
