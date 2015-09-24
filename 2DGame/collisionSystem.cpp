#include "collisionSystem.h"

#define _USE_MATH_DEFINES
#include <cmath>
#define M_PI 3.14159265358979323846

#include "terrainComponent.h"
#include "globals.h"
#include "logger.h"

/*TODO:
- CAPSULES (all)
- Get a better collisionType, where you can choose what types of objects you actually want to collide with.
- Quadtrees
- Add other collision information such as minimum translation units...
- Make the friendship between collision and impact systems closer :)
*/
SystemID CollisionSystem::ID;

CollisionSystem::CollisionSystem()
{
    std::vector<ComponentID> subList1;
    //Components needed to subscribe to system
    subList1.push_back(WorldComponent::getStaticID());
    subList1.push_back(ColliderComponent::getStaticID());
    addSubList(subList1);

    std::vector<ComponentID> subList2;
    //Components needed to subscribe to system
    subList2.push_back(WorldComponent::getStaticID());
    subList2.push_back(TerrainComponent::getStaticID());
    addSubList(subList2);
}
CollisionSystem::~CollisionSystem(){}

glm::vec2 getRotatedPoint(glm::vec2 point, float angle, glm::vec2 scale)
{
    float s = std::sin(angle * M_PI / 180.0);
    float c = std::cos(angle * M_PI / 180.0);

    //scale the point?
    point.x *= scale.x;
    point.y *= scale.y;

    // rotate point
    float xnew = point.x * c - point.y * s;
    float ynew = point.x * s + point.y * c;

    return glm::vec2(xnew, ynew);
}

float sq(float in)
{
    return in*in;
}

float distanceSq(glm::vec2 a, glm::vec2 b)
{
    return sq(a.x-b.x)+sq(a.y-b.y);
}

bool LineToLine(glm::vec2 a,glm::vec2 b,glm::vec2 c,glm::vec2 d)
{
    float den = ((d.y-c.y)*(b.x-a.x)-(d.x-c.x)*(b.y-a.y));
    float num1 = ((d.x - c.x)*(a.y-c.y) - (d.y- c.y)*(a.x-c.x));
    float num2 = ((b.x-a.x)*(a.y-c.y)-(b.y-a.y)*(a.x-c.x));
    float u1 = num1/den;
    float u2 = num2/den;
    /*if (den == 0 && num1  == 0 && num2 == 0)
        /* The two lines are coincidents
        return false;*/
    if (den == 0)
        /* The two lines are parallel */
        return false;
    if (u1 <0 || u1 > 1 || u2 < 0 || u2 > 1)
        /* Lines do not collide */
        return false;
    /* Lines DO collide */
    return true;
}

void CollisionSystem::update()
{
    for(int sub2ID = 0; sub2ID < subscribedEntities[1].size(); sub2ID++)
    {
        //Loop through all terrains to clear previous collisions
        Entity * terrain = entities[subscribedEntities[1][sub2ID]];
        TerrainComponent* terrainComp = static_cast<TerrainComponent*>(terrain->getComponent(TerrainComponent::getStaticID()));
        terrainComp->collisionData = std::vector<std::shared_ptr<CollisionImpact>>();
    }
    for(int subID = 0; subID < subscribedEntities[0].size(); subID++) //build loop
    {
        Entity * entity = entities[subscribedEntities[0][subID]];
        //First lets recalculate all corners for the collision points and any other information we need for collision. This is done for all colliders
        //Get the rotated points...
        WorldComponent* worldComp = static_cast<WorldComponent*>(entity->getComponent(WorldComponent::getStaticID()));
        ColliderComponent* colliderComp = static_cast<ColliderComponent*>(entity->getComponent(ColliderComponent::getStaticID()));
        //First lets clear all previous collisions
        colliderComp->collisionData = std::vector<std::shared_ptr<CollisionImpact>>();
        //Lets then check for changes in the object
        if(worldComp->rotation != colliderComp->previousRotation ||
           worldComp->position.x != colliderComp->previousPosition.x ||
           worldComp->position.y != colliderComp->previousPosition.y ||
           worldComp->scale.x != colliderComp->previousScale.x ||
           worldComp->scale.y != colliderComp->previousScale.y) //Rotation, scale or position has changed. Darn. We have to update it and the points!
        {
            if(colliderComp->type == 0)//box
            {
                colliderComp->corner1 = getRotatedPoint(glm::vec2(-colliderComp->widthX/2, colliderComp->heightY/2), worldComp->rotation, worldComp->scale);//topleft
                colliderComp->corner2 = getRotatedPoint(glm::vec2(colliderComp->widthX/2, colliderComp->heightY/2), worldComp->rotation, worldComp->scale);//topright
                colliderComp->corner3 = getRotatedPoint(glm::vec2(colliderComp->widthX/2, -colliderComp->heightY/2), worldComp->rotation, worldComp->scale);//btmright
                colliderComp->corner4 = getRotatedPoint(glm::vec2(-colliderComp->widthX/2, -colliderComp->heightY/2), worldComp->rotation, worldComp->scale);//btmleft
                if(worldComp->scale.x != colliderComp->previousScale.x && worldComp->scale.y != colliderComp->previousScale.y) //stop sqrting unless scale is changed
                    colliderComp->maxDistance = sqrt(sq((colliderComp->widthX/2)*worldComp->scale.x) + sq((colliderComp->heightY/2)*worldComp->scale.y));
            }
            else if(colliderComp->type == 1)//capsule
            {
                colliderComp->corner1 = getRotatedPoint(glm::vec2(-colliderComp->widthX/2, colliderComp->heightY/2-colliderComp->widthX/2), worldComp->rotation, worldComp->scale);//topleft
                colliderComp->corner2 = getRotatedPoint(glm::vec2(colliderComp->widthX/2, colliderComp->heightY/2-colliderComp->widthX/2), worldComp->rotation, worldComp->scale);//topright
                colliderComp->corner3 = getRotatedPoint(glm::vec2(colliderComp->widthX/2, -colliderComp->heightY/2+colliderComp->widthX/2), worldComp->rotation, worldComp->scale);//btmright
                colliderComp->corner4 = getRotatedPoint(glm::vec2(-colliderComp->widthX/2, -colliderComp->heightY/2+colliderComp->widthX/2), worldComp->rotation, worldComp->scale);//btmleft
                colliderComp->maxDistance = colliderComp->heightY/2*worldComp->scale.y;
            }
            else if(colliderComp->type == 2)//circle
            {
                if(colliderComp->widthX*worldComp->scale.x > colliderComp->heightY*worldComp->scale.y)
                    colliderComp->maxDistance = colliderComp->widthX/2*worldComp->scale.x;
                else
                    colliderComp->maxDistance = colliderComp->heightY/2*worldComp->scale.y;
            }
            //Reset previous for efficiency
            colliderComp->previousRotation = worldComp->rotation;
            colliderComp->previousPosition = worldComp->position;
            colliderComp->previousScale = worldComp->scale;
        }


        if(colliderComp->collisionType == 1)//no terrain collision, skip the following loop
            continue;
        //At the same time lets test all the colliders against the terrain since this doesnt involve multiple colliders
        for(int sub2ID = 0; sub2ID < subscribedEntities[1].size(); sub2ID++)
        {
            //Loop through all terrains
            Entity * terrain = entities[subscribedEntities[1][sub2ID]];
            WorldComponent* terrainWorld = static_cast<WorldComponent*>(terrain->getComponent(WorldComponent::getStaticID()));
            TerrainComponent* terrainComp = static_cast<TerrainComponent*>(terrain->getComponent(TerrainComponent::getStaticID()));
            //Relies on surface vertices being in order.
            //Find the furthest vertex on either side also using binary searches.
            //Right hand side
            float sideRightX = (worldComp->position.x + colliderComp->offsetPos.x)+((colliderComp->widthX/2)*worldComp->scale.x);//position of max right side.
            int minIndex = 0;
            int maxIndex = terrainComp->surface.size();
            int middleIndex;
            int closeRightIndex;
            while(minIndex < maxIndex)
            {
                middleIndex = (minIndex+maxIndex)/2;//Middle of array
                if(sideRightX > (terrainComp->surface[middleIndex].x*terrainWorld->scale.x)+terrainWorld->position.x)
                    minIndex = middleIndex + 1;
                else
                    maxIndex = middleIndex;
            }
            closeRightIndex = maxIndex;
            //Left hand side
            float sideLeftX = (worldComp->position.x + colliderComp->offsetPos.x)-((colliderComp->widthX/2)*worldComp->scale.x);//position of max left side.
            minIndex = 0;
            maxIndex = terrainComp->surface.size();
            int closeLeftIndex;
            while(minIndex < maxIndex)
            {
                middleIndex = (minIndex+maxIndex)/2;//Middle of array
                if(sideLeftX > (terrainComp->surface[middleIndex].x*terrainWorld->scale.x)+terrainWorld->position.x)
                    minIndex = middleIndex + 1;
                else
                    maxIndex = middleIndex;
            }
            closeLeftIndex = maxIndex;

            //Test all points/lines inside these two binary search bounds against collider shape
            if(colliderComp->type == 0)//box
            {
                glm::vec2 centre1 = worldComp->position + colliderComp->offsetPos;

                //Corners of box
                glm::vec2 topleft = centre1 + colliderComp->corner1; //topleft
                glm::vec2 topright = centre1 + colliderComp->corner2; //topright
                glm::vec2 btmright = centre1 + colliderComp->corner3; //btmright
                glm::vec2 btmleft = centre1 + colliderComp->corner4; //btmleft
                for(int i = closeLeftIndex-1; i < closeRightIndex+1; i++)
                {
                    glm::vec2 lineSurface1 = (terrainComp->surface[i]*terrainWorld->scale)+terrainWorld->position;
                    glm::vec2 lineSurface2 = (terrainComp->surface[i+1]*terrainWorld->scale)+terrainWorld->position;
                    if(LineToLine(topleft, topright, lineSurface1, lineSurface2) ||
                       LineToLine(topright, btmright, lineSurface1, lineSurface2) ||
                       LineToLine(btmright, btmleft, lineSurface1, lineSurface2) ||
                       LineToLine(btmleft, topleft, lineSurface1, lineSurface2))
                    {
                        //Add the collisions to both terrain and other collider comps...
                        terrainComp->collisionData.push_back(std::make_shared<CollisionImpact>(CollisionImpact(subscribedEntities[0][subID])));//Add collided entity to terrain list
                        //colliderComp->collisionData.push_back(new CollisionImpact(subscribedEntities[1][sub2ID]));//Add terrain entity to collided list
                        break;
                    }
                }
            }
            /*else if(colliderComp->type == 1) //capsule LOL
            {

            }
            else if(colliderComp->type == 2) //circle
            {

            }*/
            //Logger()<<closeLeftIndex<<" "<<closeRightIndex<<" close"<<std::endl;
        }
    }

    for(int subID = 0; subID < subscribedEntities[0].size(); subID++) //Test multiple colliders against each other loop
    {
        //TODO: Collision types and object types. So ObjectType is the type you are. and Collision type is the type you want to collide with
        //(in second loop) if collision type == object type then proceed with collision
        Entity * occupantTest = entities[subscribedEntities[0][subID]];
        WorldComponent* occWorld = static_cast<WorldComponent*>(occupantTest->getComponent(WorldComponent::getStaticID()));
        ColliderComponent* occCollide = static_cast<ColliderComponent*>(occupantTest->getComponent(ColliderComponent::getStaticID()));
        if(occCollide->collisionType == 0)//no object collision, skip testing
            continue;
        //Only test colliders which havent already been tested yet
        for(int popID = subscribedEntities[0].size()-1; popID > subID; popID--)
        {
            Entity * observerTest = entities[subscribedEntities[0][popID]];
            WorldComponent* obsWorld = static_cast<WorldComponent*>(observerTest->getComponent(WorldComponent::getStaticID()));
            ColliderComponent* obsCollide = static_cast<ColliderComponent*>(observerTest->getComponent(ColliderComponent::getStaticID()));
            if(obsCollide->collisionType == 0)//no object collision, skip testing
                continue;
            //check something hasn't gone wrong.
            if(subID == popID)
                Logger()<<"Trying to collide with self - destruction soon"<<std::endl;
            //Do a quick circle to circle of the maximum, this will improve efficiency.
            if (CircleToCircle(occWorld, occCollide, obsWorld, obsCollide))
            {
                //More complex detection depending on type.
                bool collisionExists = false;

                if(occCollide->type == 0)//box
                {
                    if(obsCollide->type == 0)//box to box
                    {
                        if(BoxToBox(occWorld, occCollide, obsWorld, obsCollide))
                            collisionExists = true;
                    }
                    else if(obsCollide->type == 1)//box to capsule
                    {
                        if(BoxToCapsule(occWorld, occCollide, obsWorld, obsCollide))//make sure u get the right order!
                            collisionExists = true;
                    }
                    else if(obsCollide->type == 2)//box to circle
                    {
                        if(BoxToCircle(occWorld, occCollide, obsWorld, obsCollide))
                            collisionExists = true;
                    }
                }
                else if(occCollide->type == 1)//capsule
                {
                    if(obsCollide->type == 0)//capsule to box
                    {
                        if(BoxToCapsule(obsWorld, obsCollide, occWorld, occCollide))
                            collisionExists = true;
                    }
                    /*else if(obsCollide->type == 1)//capsule to capsule
                    {
                        if(CapsuleToCapsule(occWorld, occCollide, obsWorld, obsCollide))//make sure u get the right order!
                            collisionExists = true;
                    }
                    /*else if(obsCollide->type == 2)//capsule to circle
                    {
                        if(CircleToCapsule(occWorld, occCollide, obsWorld, obsCollide))
                            collisionExists = true;
                    }*/
                }
                else if(occCollide->type == 2)//circle
                {
                    if(obsCollide->type == 0)//circle to box
                    {
                        if(BoxToCircle(obsWorld, obsCollide, occWorld, occCollide))
                            collisionExists = true;
                    }
                    /*else if(obsCollide->type == 1)//circle to capsule
                    {
                        if(CircleToCapsule(occWorld, occCollide, obsWorld, obsCollide))
                            collisionExists = true;
                    }*/
                    else if(obsCollide->type == 2)//circle to circle
                    {
                        collisionExists = true;
                    }
                }

                if(collisionExists)
                {
                    //add collision objects to list, also have other information (minimum translation vector etc.)
                    //Add the collisions to both collider comps...
                    obsCollide->collisionData.push_back(std::make_shared<CollisionImpact>(CollisionImpact(subscribedEntities[0][subID])));//Add occupant to observer list
                    occCollide->collisionData.push_back(std::make_shared<CollisionImpact>(CollisionImpact(subscribedEntities[0][popID])));//Add observer to occupant list
                }
            }
        }
    }
}

bool CollisionSystem::CircleToCircle(WorldComponent * oneW, ColliderComponent * oneC, WorldComponent * twoW, ColliderComponent * twoC)
{
    glm::vec2 centre1 = oneW->position + oneC->offsetPos;
    glm::vec2 centre2 = twoW->position + twoC->offsetPos;
    if(sq(centre2.x-centre1.x) + sq(centre2.y-centre1.y) <= sq(oneC->maxDistance+twoC->maxDistance))
        return true;
    return false;
}

bool CollisionSystem::BoxToBox(WorldComponent * oneW, ColliderComponent * oneC, WorldComponent * twoW, ColliderComponent * twoC)
{
    //SAT FOR ROTATED
    glm::vec2 centre1 = oneW->position + oneC->offsetPos;
    glm::vec2 centre2 = twoW->position + twoC->offsetPos;
    //Axes of both boxes
    glm::vec2 axes[4];
    axes[0] = (oneC->corner2-oneC->corner1);
    axes[1] = (oneC->corner2-oneC->corner3);
    axes[2] = (twoC->corner2-twoC->corner1);
    axes[3] = (twoC->corner2-twoC->corner3);

    //Corners of both boxes
    glm::vec2 boxCorners1[4];
    boxCorners1[0] = centre1 + oneC->corner1; //topleft
    boxCorners1[1] = centre1 + oneC->corner2; //topright
    boxCorners1[2] = centre1 + oneC->corner3; //btmright
    boxCorners1[3] = centre1 + oneC->corner4; //btmleft

    glm::vec2 boxCorners2[4];
    boxCorners2[0] = centre2 + twoC->corner1; //topleft
    boxCorners2[1] = centre2 + twoC->corner2; //topright
    boxCorners2[2] = centre2 + twoC->corner3; //btmright
    boxCorners2[3] = centre2 + twoC->corner4; //btmleft

    for(int i = 0; i < 4; i++)//axes
    {
        float minDot1 = 0;
        float maxDot1 = 0;
        float minDot2 = 0;
        float maxDot2 = 0;
        glm::vec2 axis = axes[i];
        for(int j = 0; j < 4; j++)//box1 corners
        {
            glm::vec2 between = boxCorners1[i] - boxCorners1[j];
            float dot = glm::dot(axis, between);
            if(j == 0)
            {
                minDot1 = dot;
                maxDot1 = dot;
            }
            else
            {
                if(dot < minDot1)
                    minDot1 = dot;
                if(dot > maxDot1)
                    maxDot1 = dot;
            }
        }
        for(int j = 0; j < 4; j++)//box2 corners
        {
            glm::vec2 between = boxCorners1[i] - boxCorners2[j];
            float dot = glm::dot(axis, between);
            if(j == 0)
            {
                minDot2 = dot;
                maxDot2 = dot;
            }
            else
            {
                if(dot < minDot2)
                    minDot2 = dot;
                if(dot > maxDot2)
                    maxDot2 = dot;
            }
        }
        if(!(minDot1 <= maxDot2 && maxDot1 >= minDot2))
            return false;
    }
    return true;
}

bool CollisionSystem::BoxToCapsule(WorldComponent * boxW, ColliderComponent * boxC, WorldComponent * capW, ColliderComponent * capC)
{
    //TODO CAPSULES
    /*//SAT FOR ROTATED
    glm::vec2 centre1 = boxW->position + boxC->offsetPos;
    glm::vec2 centre2 = capW->position + capC->offsetPos;

    //Corners of both boxes
    glm::vec2 boxCorners1[4];
    boxCorners1[0] = centre1 + boxC->corner1; //topleft
    boxCorners1[1] = centre1 + boxC->corner2; //topright
    boxCorners1[2] = centre1 + boxC->corner3; //btmright
    boxCorners1[3] = centre1 + boxC->corner4; //btmleft

    glm::vec2 boxCorners2[4];
    boxCorners2[0] = centre2 + capC->corner1; //topleft
    boxCorners2[1] = centre2 + capC->corner2; //topright
    boxCorners2[2] = centre2 + capC->corner3; //btmright
    boxCorners2[3] = centre2 + capC->corner4; //btmleft

    glm::vec2 midPointA2 = (boxCorners2[0]+boxCorners2[1])/2;
    glm::vec2 midPointB2 = (boxCorners2[2]+boxCorners2[3])/2;

    //Axes of both boxes
    glm::vec2 axes[5];
    axes[0] = (boxC->corner2-boxC->corner1);
    axes[1] = (boxC->corner2-boxC->corner3);
    //Find closest point on box for circle axis.
    float minDistance;
    int minIndex;
    for(int i = 0; i < 4; i++)
    {
        float d = distanceSq(boxCorners1[i], centre2);
        if(i == 0)
        {
            minDistance = d;
            minIndex = i;
        }
        else
            if(d < minDistance)
            {
                minDistance = d;
                minIndex = i;
            }
    }
    axes[2] = (midPointA2-boxCorners1[minIndex]);
    //Find closest point on box for circle axis.
    for(int i = 0; i < 4; i++)
    {
        float d = distanceSq(boxCorners1[i], centre2);
        if(i == 0)
        {
            minDistance = d;
            minIndex = i;
        }
        else
            if(d < minDistance)
            {
                minDistance = d;
                minIndex = i;
            }
    }
    axes[3] = (midPointB2-boxCorners1[minIndex]);
    axes[4] = (midPointA2-midPointB2);

    for(int i = 0; i < 3; i++)//axes
    {
        float minDot1 = 0;
        float maxDot1 = 0;
        float minDot2 = -capC->widthX*capW->scale.x;
        float maxDot2 = cirC->maxDistance;
        glm::vec2 axis = axes[i];
        for(int j = 0; j < 4; j++)//box1 corners
        {
            glm::vec2 between = centre2 - boxCorners1[j];
            float dot = glm::dot(axis, between);
            if(j == 0)
            {
                minDot1 = dot;
                maxDot1 = dot;
            }
            else
            {
                if(dot < minDot1)
                    minDot1 = dot;
                if(dot > maxDot1)
                    maxDot1 = dot;
            }
        }
        if(!(minDot1 <= maxDot2 && maxDot1 >= minDot2))
            return false;
    }
    return true;*/
}

bool CollisionSystem::BoxToCircle(WorldComponent * boxW, ColliderComponent * boxC, WorldComponent * cirW, ColliderComponent * cirC)
{
    //SAT FOR ROTATED
    glm::vec2 centre1 = boxW->position + boxC->offsetPos;
    glm::vec2 centre2 = cirW->position + cirC->offsetPos;

    //Corners of box
    glm::vec2 boxCorners1[4];
    boxCorners1[0] = centre1 + boxC->corner1; //topleft
    boxCorners1[1] = centre1 + boxC->corner2; //topright
    boxCorners1[2] = centre1 + boxC->corner3; //btmright
    boxCorners1[3] = centre1 + boxC->corner4; //btmleft

    //Axes of both box and circle
    glm::vec2 axes[3];
    axes[0] = (boxC->corner2-boxC->corner1);
    axes[1] = (boxC->corner2-boxC->corner3);

    //Find closest point on box for circle axis.
    float minDistance;
    int minIndex;
    for(int i = 0; i < 4; i++)
    {
        float d = distanceSq(boxCorners1[i], centre2);
        if(i == 0)
        {
            minDistance = d;
            minIndex = i;
        }
        else
            if(d < minDistance)
            {
                minDistance = d;
                minIndex = i;
            }
    }
    axes[2] = (centre2-boxCorners1[minIndex]);

    for(int i = 0; i < 3; i++)//axes
    {
        float minDot1 = 0;
        float maxDot1 = 0;
        float minDot2 = -cirC->maxDistance;
        float maxDot2 = cirC->maxDistance;
        glm::vec2 axis = axes[i];
        for(int j = 0; j < 4; j++)//box1 corners
        {
            glm::vec2 between = centre2 - boxCorners1[j];
            float dot = glm::dot(axis, between);
            if(j == 0)
            {
                minDot1 = dot;
                maxDot1 = dot;
            }
            else
            {
                if(dot < minDot1)
                    minDot1 = dot;
                if(dot > maxDot1)
                    maxDot1 = dot;
            }
        }
        if(!(minDot1 <= maxDot2 && maxDot1 >= minDot2))
            return false;
    }
    return true;
}
