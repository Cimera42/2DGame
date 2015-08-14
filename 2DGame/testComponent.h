#ifndef TESTCOMPONENT_H_INCLUDED
#define TESTCOMPONENT_H_INCLUDED

#include "component.h"

class TestComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        TestComponent();
        virtual ~TestComponent();

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // TESTCOMPONENT_H_INCLUDED
