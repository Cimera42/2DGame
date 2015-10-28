#ifndef PLAYERCOMPONENT_H_INCLUDED
#define PLAYERCOMPONENT_H_INCLUDED

#include "component.h"

class PlayerComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        PlayerComponent(int inTeamID);
        virtual ~PlayerComponent();

        int teamID;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // PLAYERCOMPONENT_H_INCLUDED
