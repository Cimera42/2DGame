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
        ProjectileComponent* construct();
        ProjectileComponent* construct(std::vector<std::string>);
        ProjectileComponent* clone() {return new ProjectileComponent(*this);}

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // PROJECTILECOMPONENT_H_INCLUDED
