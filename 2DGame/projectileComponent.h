#ifndef PROJECTILECOMPONENT_H_INCLUDED
#define PROJECTILECOMPONENT_H_INCLUDED

#include "component.h"

class ProjectileComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        ProjectileComponent();
        virtual ~ProjectileComponent();

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // PROJECTILECOMPONENT_H_INCLUDED
