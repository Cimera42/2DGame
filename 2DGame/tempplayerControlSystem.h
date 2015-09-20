#ifndef TEMPPLAYERCONTROLSYSTEM_H_INCLUDED
#define TEMPPLAYERCONTROLSYSTEM_H_INCLUDED

#include "system.h"

class PlayerControlSystem : public System
{
    private:
        static SystemID ID;

    public:
        PlayerControlSystem();
        virtual ~PlayerControlSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update(float);
};

#endif // TEMPPLAYERCONTROLSYSTEM_H_INCLUDED
