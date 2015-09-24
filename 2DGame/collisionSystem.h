#ifndef COLLISIONSYSTEM_H_INCLUDED
#define COLLISIONSYSTEM_H_INCLUDED

#include "system.h"
#include "worldComponent.h"
#include "colliderComponent.h"

class CollisionSystem : public System
{
    private:
        static SystemID ID;

    public:
        CollisionSystem();
        virtual ~CollisionSystem();

        //Auto generation of ID
        SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        void update();

        //collision types
        bool CircleToCircle(WorldComponent * oneW, ColliderComponent * oneC, WorldComponent * twoW, ColliderComponent * twoC);
        bool BoxToBox(WorldComponent * oneW, ColliderComponent * oneC, WorldComponent * twoW, ColliderComponent * twoC);
        bool BoxToCapsule(WorldComponent * boxW, ColliderComponent * boxC, WorldComponent * capW, ColliderComponent * capC);
        bool BoxToCircle(WorldComponent * boxW, ColliderComponent * boxC, WorldComponent * cirW, ColliderComponent * cirC);

        std::vector<Entity*> colliding;//need to also store who with? extra info? etc.
};

#endif // COLLISIONSYSTEM_H_INCLUDED
