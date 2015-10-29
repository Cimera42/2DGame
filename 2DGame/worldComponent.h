#ifndef WORLDCOMPONENT_H_INCLUDED
#define WORLDCOMPONENT_H_INCLUDED

#include "component.h"
#include <glm/glm.hpp>

class WorldComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        WorldComponent();
        virtual ~WorldComponent();
        WorldComponent* construct(glm::vec2,glm::vec2,float);
        WorldComponent* construct(std::vector<std::string>);
        WorldComponent* clone() {return new WorldComponent(*this);}

        glm::vec2 position;
        glm::vec2 scale;
        float rotation;

        glm::mat4 modelMatrix;

        void updateMatrix();

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // WORLDCOMPONENT_H_INCLUDED
