#ifndef TERRAINIMPACTSYSTEM_H_INCLUDED
#define TERRAINIMPACTSYSTEM_H_INCLUDED

#include "system.h"
#include "openGLFunctions.h"
#include <glm/glm.hpp>

/*Only impact system. Only handles normal force of object */

class TerrainImpactSystem : public System
{
    private:
        static SystemID ID;

    public:
        TerrainImpactSystem();
        virtual ~TerrainImpactSystem();


        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // TERRAINIMPACTSYSTEM_H_INCLUDED
