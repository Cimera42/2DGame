#ifndef TESTSYSTEM_H_INCLUDED
#define TESTSYSTEM_H_INCLUDED

#include "system.h"

class TestSystem : public System
{
    private:
        static SystemID ID;

    public:
        TestSystem();
        virtual ~TestSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();
};

#endif // TESTSYSTEM_H_INCLUDED
