#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

typedef int ComponentID;

class Component
{
    private:
        static ComponentID ID;

    public:
        Component();
        virtual ~Component();

        bool enabled = true;

        //Auto generation of ID
        static ComponentID componentIDIncrementor;
        virtual ComponentID getID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
        static ComponentID getStaticID() {if(ID == 0) {ID = componentIDIncrementor++;} return ID;}
};

#endif // COMPONENT_H_INCLUDED
