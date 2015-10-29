#ifndef COLLIDERCOMPONENT_H_INCLUDED
#define COLLIDERCOMPONENT_H_INCLUDED

#include "component.h"
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class CollisionPair
{
    public:
        CollisionPair(int inCollisionEntityID, int inCollisionEntityID2);
        ~CollisionPair();

        bool processed = false;

        int collisionEntityOne; //Entity ID of the colliding object 1
        int collisionEntityTwo; //Entity ID of the colliding object 2
        glm::vec2 minimumTranslation; //Minimum translation to move out of collision. - retieve through get


        /*Data for use in systems*/
        int getCollisionPairID(int entityID); //First step is to use this to check for the correct entity - input either entity ID to retrieve pairID
        int getCollisionEntityID(int pairID); //input pairID to get its entityID
        int getOppositePairID(int pairID); //input the known pairID to get opposing ID
        int getOppositeEntityID(int pairID); //input the pairID to get opposing entityID
        glm::vec2 getMinimumTranslation(int pairID); //input 1 or 2 to retrieve the data of entity1 or 2;
};

class ColliderComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        ColliderComponent();
        virtual ~ColliderComponent();
        ColliderComponent* construct(std::string inType, std::string inCollisionType, glm::vec2 inOffsetPos, float inWidth, float inHeight);
        ColliderComponent* construct(std::vector<std::string>);
        ColliderComponent* clone() {return new ColliderComponent(*this);}

        //All values are to be considered before scaling
        glm::vec2 offsetPos; //center of the object offset from world
        float widthX;
        float heightY;
        int type; //0 = bounding box, 1 = capsule, 2 = circle,  - this is for internal use
        int collisionType; //0 = terrain only, 1 = object only, 2 = both object and terrain,  - this is for internal use

        //Stored for calculations, do not edit except in collision system
        glm::vec2 corner1; //top left
        glm::vec2 corner2; //top right
        glm::vec2 corner3; //bottom right
        glm::vec2 corner4; //bottom left
        float maxDistance; //sqrt if box, otherwise non-sqrt. Simply the radius

        //Previous for recalculation check
        float previousRotation;
        glm::vec2 previousScale;
        glm::vec2 previousPosition;

        //Data if collision has occured
        std::vector<std::shared_ptr<CollisionPair>> collisionData;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // COLLIDERCOMPONENT_H_INCLUDED
