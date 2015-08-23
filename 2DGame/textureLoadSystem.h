#ifndef TEXTURELOADSYSTEM_H_INCLUDED
#define TEXTURELOADSYSTEM_H_INCLUDED

#include "system.h"
#include "openGLFunctions.h"
#include <pthread.h>

struct TextureToLoad
{
    public:
        GLuint* idLoc;
        int width, height;
        unsigned char* data;
        bool srgb;
};
extern pthread_mutex_t textureLoadMutex;
extern std::vector<TextureToLoad> texturesToLoad;

class TextureLoadSystem : public System
{
    private:
        static SystemID ID;

    public:
        TextureLoadSystem();
        virtual ~TextureLoadSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // TEXTURELOADSYSTEM_H_INCLUDED
