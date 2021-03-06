#ifndef TERRAINCOMPONENT_H_INCLUDED
#define TERRAINCOMPONENT_H_INCLUDED

#include "component.h"
#include "openGLFunctions.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "textureStore.h"

#include "colliderComponent.h"

class TerrainComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        TerrainComponent();
        virtual ~TerrainComponent();
        TerrainComponent* construct(int numPoints, float heightScale, float noiseScale, float inBaseline);
        TerrainComponent* construct(std::vector<std::string>);
        TerrainComponent* clone() {return new TerrainComponent(*this);}

        //Generated data and points
        std::vector<glm::vec2> surface;
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> indices;

        //Data for GPU
        GLuint VAO;
        bool loadedVAO = false;
        GLuint vertexBuffer;
        GLuint uvBuffer;
        GLuint indexBuffer;
        int bufSize;

        TextureStore* textureStore;

        //Data if collisions habe occured with terrain (should this be here, who knows)
        std::vector<std::shared_ptr<CollisionPair>> collisionData;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}

        void rebuildBuffers();
};

#endif // TERRAINCOMPONENT_H_INCLUDED
