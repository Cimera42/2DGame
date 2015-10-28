#ifndef PROJECTILECOLLIDESYSTEM_H_INCLUDED
#define PROJECTILECOLLIDESYSTEM_H_INCLUDED

#include "system.h"
#include "openGLFunctions.h"
#include <glm/glm.hpp>

/*
This system is used to handle anything that the projectiles are colliding with.
*/

class ProjectileCollideSystem : public System
{
    private:
        static SystemID ID;

    public:
        ProjectileCollideSystem();
        virtual ~ProjectileCollideSystem();


        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // PROJECTILECOLLIDESYSTEM_H_INCLUDED
