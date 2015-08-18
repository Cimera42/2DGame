#ifndef WINDOWSYSTEM_H_INCLUDED
#define WINDOWSYSTEM_H_INCLUDED

#include "system.h"

class WindowSystem : public System
{
    private:
        static SystemID ID;

    public:
        WindowSystem();
        virtual ~WindowSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // WINDOWSYSTEM_H_INCLUDED
