#ifndef PLAYERCOMPONENT_H_INCLUDED
#define PLAYERCOMPONENT_H_INCLUDED

#include "component.h"

class PlayerComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        PlayerComponent();
        virtual ~PlayerComponent();
        PlayerComponent* construct(int);
        PlayerComponent* construct(std::vector<std::string>);
        PlayerComponent* clone() {return new PlayerComponent(*this);}

        int teamID;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // PLAYERCOMPONENT_H_INCLUDED
