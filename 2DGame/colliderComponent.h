#ifndef COLLIDERCOMPONENT_H_INCLUDED
#define COLLIDERCOMPONENT_H_INCLUDED

#include "component.h"
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class CollisionImpact
{
    public:
        CollisionImpact(int inCollisionEntityID);
        ~CollisionImpact();

        int collisionEntityID; //Entity ID of the colliding object
        //glm::vec2 minimumTranslation; //Minimum translation to move out of collision.
        //- whatever system implements this can choose to use this data or not
        //Eg. ProjectileImpactSystem may choose to use this data whilst PlayerImpactSystem may not.
};

class ColliderComponent : public Component
{
    private:
        static ComponentID ID;

    public:
        ColliderComponent(std::string inType, std::string inCollisionType, glm::vec2 inOffsetPos, float inWidth, float inHeight);
        virtual ~ColliderComponent();

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
        std::vector<std::shared_ptr<CollisionImpact>> collisionData;

        //Auto generation of ID
        ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // COLLIDERCOMPONENT_H_INCLUDED
