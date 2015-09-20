#ifndef MOTIONSYSTEM_H_INCLUDED
#define MOTIONSYSTEM_H_INCLUDED

#include "system.h"

class MotionSystem : public System
{
    private:
        static SystemID ID;

    public:
        MotionSystem();
        virtual ~MotionSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update(float);
};

#endif // MOTIONSYSTEM_H_INCLUDED
