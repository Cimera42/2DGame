#ifndef MOVEMENTSYSTEM_H_INCLUDED
#define MOVEMENTSYSTEM_H_INCLUDED

#include "system.h"

class MovementSystem : public System
{
    private:
        static SystemID ID;

    public:
        MovementSystem();
        virtual ~MovementSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update(float);
};

#endif // MOVEMENTSYSTEM_H_INCLUDED
