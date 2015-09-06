#ifndef TERRAINCOMPONENT_H_INCLUDED
#define TERRAINCOMPONENT_H_INCLUDED

#include "component.h"
#include "openGLFunctions.h"
#include <glm/glm.hpp>
#include <vector>
#include "textureStore.h"

class TerrainComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        TerrainComponent(int, float);
        virtual ~TerrainComponent();

        std::vector<glm::vec2> surface;
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> indices;

        GLuint VAO;
        bool loadedVAO = false;
        GLuint vertexBuffer;
        GLuint uvBuffer;
        GLuint indexBuffer;
        int bufSize;

        TextureStore* textureStore;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}

        void rebuildBuffers();
};

#endif // TERRAINCOMPONENT_H_INCLUDED
