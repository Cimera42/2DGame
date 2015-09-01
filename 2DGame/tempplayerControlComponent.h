#ifndef TEMPPLAYERCONTROLCOMPONENT_H_INCLUDED
#define TEMPPLAYERCONTROLCOMPONENT_H_INCLUDED

#include "component.h"

class PlayerControlComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        PlayerControlComponent(float,int,int,int,int);
        virtual ~PlayerControlComponent();

        float speed;
        int upKey;
        int downKey;
        int leftKey;
        int rightKey;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // TEMPPLAYERCONTROLCOMPONENT_H_INCLUDED
