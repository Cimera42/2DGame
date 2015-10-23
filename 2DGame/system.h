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
        std::vector<std::vector<ComponentID> > componentSubList;
        void addSubList(std::vector<ComponentID>);

        std::vector<std::vector<EntityID> > subscribedEntities;
        bool checkComponent(ComponentID, int);
        bool checkEntityComponents(Entity*, int);
        int checkEntityAlreadySubscribed(EntityID, int);
        bool subscribe(Entity*, ComponentID);
        bool unsubscribeByComponent(Entity*, ComponentID);
        bool unsubscribe(Entity*);
        virtual void entitySubscribed(Entity*,int){}
        virtual void entityUnsubscribed(Entity*,int){}

        virtual void update();
        virtual void update(float inDelta);
};

//Attempt to subscribe entity to all systems
void subscribeToSystems(Entity*, ComponentID);
//Attempt to unsubscribe entity to all systems
void unsubscribeToSystemsByComponent(Entity*, ComponentID);
void unsubscribeToSystems(Entity*);

#endif // SYSTEM_H_INCLUDED
