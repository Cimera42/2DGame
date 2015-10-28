#ifndef LIFETIMECOMPONENT_H_INCLUDED
#define LIFETIMECOMPONENT_H_INCLUDED

#include "component.h"

class lifetimeComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        lifetimeComponent();
        virtual ~lifetimeComponent();

        //timer
        //delete entity after time runs out?

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // LIFETIMECOMPONENT_H_INCLUDED
