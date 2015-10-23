#ifndef IMPACTTERRAINSYSTEM_H_INCLUDED
#define IMPACTTERRAINSYSTEM_H_INCLUDED

#include "system.h"
#include "openGLFunctions.h"
#include <glm/glm.hpp>

/*
This system is used to handle anything that is colliding with the terrain through
the terrains only.

*/

class ImpactTerrainSystem : public System
{
    private:
        static SystemID ID;

    public:
        ImpactTerrainSystem();
        virtual ~ImpactTerrainSystem();


        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // IMPACTTERRAINSYSTEM_H_INCLUDED
