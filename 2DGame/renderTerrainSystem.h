#ifndef RENDERTERRAINSYSTEM_H_INCLUDED
#define RENDERTERRAINSYSTEM_H_INCLUDED

#include "system.h"
#include "openGLFunctions.h"
#include <glm/glm.hpp>

#include "textureStore.h"
#include "terrainComponent.h"
#include "worldComponent.h"

class RenderTerrainSystem : public System
{
    private:
        static SystemID ID;

    public:
        RenderTerrainSystem();
        virtual ~RenderTerrainSystem();

        GLuint shader;
        GLuint textureLoc;
        GLuint modelMatLoc;

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // RENDERTERRAINSYSTEM_H_INCLUDED
