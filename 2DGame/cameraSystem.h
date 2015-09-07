#ifndef CAMERASYSTEM_H_INCLUDED
#define CAMERASYSTEM_H_INCLUDED

#include "system.h"

class CameraSystem : public System
{
    private:
        static SystemID ID;

    public:
        CameraSystem();
        virtual ~CameraSystem();

        EntityID activeCamera;

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void entitySubscribed(Entity*,int);
        void update();

        void setActiveCamera(EntityID);
};

#endif // CAMERASYSTEM_H_INCLUDED
