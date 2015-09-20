#ifndef MOUSESCREENCOORDSYSTEM_H_INCLUDED
#define MOUSESCREENCOORDSYSTEM_H_INCLUDED

#include "system.h"

class MouseScreenCoordSystem : public System
{
    private:
        static SystemID ID;

    public:
        MouseScreenCoordSystem();
        virtual ~MouseScreenCoordSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // MOUSESCREENCOORDSYSTEM_H_INCLUDED
