#ifndef RENDER2DCOMPONENT_H_INCLUDED
#define RENDER2DCOMPONENT_H_INCLUDED

#include "component.h"
#include <glm/glm.hpp>

class Render2DComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        Render2DComponent();
        virtual ~Render2DComponent();
        Render2DComponent* construct(glm::vec2 inStartUV, glm::vec2 inSize);
        Render2DComponent* construct(std::vector<std::string>);
        Render2DComponent* clone() {return new Render2DComponent(*this);}

        glm::vec2 startUV;
        glm::vec2 UVsize;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // RENDER2DCOMPONENT_H_INCLUDED
