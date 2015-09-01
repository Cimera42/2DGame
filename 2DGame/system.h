#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <vector>

typedef int EntityID;
typedef int ComponentID;
typedef int SystemID;

class Entity;
class System
{
    private:
        static SystemID ID;

    public:
        System();
        virtual ~System();

        bool enabled = true;

        //Auto generation of ID
        static SystemID systemIDIncrementor;
        virtual SystemID getID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}
        static SystemID getStaticID() {if(ID == 0) {ID = systemIDIncrementor++;} return ID;}

        //Entity subscription
        std::vector<ComponentID> componentSubList;
        std::vector<EntityID> subscribedEntities;
        bool checkComponent(ComponentID);
        bool checkEntityComponents(Entity*);
        int checkEntityAlreadySubscribed(EntityID);
        bool subscribe(Entity*, ComponentID);
        bool unsubscribe(Entity*, ComponentID);
        virtual void entitySubscribed(Entity*){}
        virtual void entityUnsubscribed(Entity*){}

        virtual void update();
};

//Attempt to subscribe entity to all systems
void subscribeToSystems(Entity*, ComponentID);
//Attempt to unsubscribe entity to all systems
void unsubscribeToSystems(Entity*, ComponentID);

#endif // SYSTEM_H_INCLUDED
