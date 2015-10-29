#ifndef CONSOLESYSTEM_H_INCLUDED
#define CONSOLESYSTEM_H_INCLUDED

#include "system.h"

class ConsoleSystem : public System
{
    private:
        static SystemID ID;

    public:
        ConsoleSystem();
        virtual ~ConsoleSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

void listComponents(EntityID inEntityID);

#endif // CONSOLESYSTEM_H_INCLUDED
