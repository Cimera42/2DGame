#ifndef RENDERSYSTEM2D_H_INCLUDED
#define RENDERSYSTEM2D_H_INCLUDED

#include "system.h"
#include "render2DComponent.h"
#include "worldComponent.h"
#include "textureStore.h"
#include <GL/glew.h>

class Render2DSystem : public System
{
    private:
        static SystemID ID;

    public:
        Render2DSystem();
        virtual ~Render2DSystem();

        GLuint shader;

        GLuint VAO;
        GLuint vertexBuffer;
        GLuint uvBuffer;
        GLuint indexBuffer;
        GLuint matrixBuffer;

        TextureStore* textureStore;
        GLuint textureLoc;
        GLuint viewProjMatLoc;

        std::vector<glm::vec2> vertices;
        std::vector<glm::vec4> uvs;
        std::vector<unsigned int> indices;
        int bufSize;
        std::vector<glm::mat4> matrices;

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        bool shouldResizeBuffers = false;
        void resizeBuffers();
        void refillBuffers();

        void addToList(WorldComponent*, Render2DComponent*);

        void entitySubscribed(Entity*,int);
        void entityUnsubscribed(Entity*,int);
        void update();
};

#endif // RENDERSYSTEM2D_H_INCLUDED
