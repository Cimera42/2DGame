#ifndef RENDERSYSTEM2D_H_INCLUDED
#define RENDERSYSTEM2D_H_INCLUDED

#include "system.h"
#include "render2DComponent.h"
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
        GLuint indexBuffer;

        glm::mat4 M;

        int bufSize;

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // RENDERSYSTEM2D_H_INCLUDED
