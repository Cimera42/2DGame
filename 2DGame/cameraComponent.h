#ifndef CAMERACOMPONENT_H_INCLUDED
#define CAMERACOMPONENT_H_INCLUDED

#include "component.h"
#include <glm/glm.hpp>

class CameraComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        CameraComponent();
        virtual ~CameraComponent();
        CameraComponent* construct(float inZoom, bool inActive);
        CameraComponent* construct(std::vector<std::string>);
        CameraComponent* clone() {return new CameraComponent(*this);}

        bool activeFlag;

        float zoom;
        glm::mat4 projectionMatrix;
        glm::mat4 jointMatrix;

        void updateMatrix();

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // CAMERACOMPONENT_H_INCLUDED
