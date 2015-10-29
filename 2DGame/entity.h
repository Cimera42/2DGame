#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <unordered_map>
#include <string>

typedef int EntityID;
typedef int ComponentID;

class Component;
class Entity
{
    public:
        Entity();
        ~Entity();

        std::string vanityName = "Unnamed Entity";

        //Incrementor for ids
        static EntityID globalEntityIncrementorID;
        //Unique id for entity
        EntityID entityID;
        EntityID getID();

        //List of components attached to entity
        std::unordered_map<ComponentID, Component*> components;

        bool addComponent(Component*);
        bool hasComponent(ComponentID);
        bool canUseComponent(ComponentID);
        Component* getComponent(ComponentID);
        bool deleteComponent(ComponentID);
};

#endif // ENTITY_H_INCLUDED
