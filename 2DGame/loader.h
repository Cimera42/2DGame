#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

///TODO:
/*
- Use smart pointers... (aparently you cannot delete a pointer that you do not assign through new)
- Control the use of the string independantly within each of the subStores - aka load datablocks and process them
- Make a version of loading work on copying/instancing from a pointer rather than pure literal string
- Find a way to put implementations of templates in .cpp
*/

/**
- All loading from the program should be evoked through the loader.
- This then sends commands to the appropriate subStore which can then process the loading as it wishes.
- The subStore will most likely then evoke other loading through either this loader or through others - Eg. textureLoading through SOIL.
**/

#include <map>
#include <string>
#include <iostream>
#include "fileReader.h"
#include "store.h"

extern std::map<std::string, Store*> internalMap;


///Distribution Classes
template <class T>
class Load
{
public:
    //scene
    static bool Object(T** returnLoc, std::string s);//objects
};

//IMPLEMENTATION - needs to be moved and the acceptable classes controlled in .cpp
template <class T>
bool Load<T>::Object(T** returnLoc, std::string s)
{
    //Loading is controlled by the string
    std::map<std::string, Store*>::iterator it = internalMap.find(s); //see if the object already exists
    if(it != internalMap.end())
    {
        //if it exists, double check name is correct,
        if(it->second->internalName == s)
        {
            //if the name matches (which it should unless its been altered, use this
            it->second->usageCount += 1;
            *returnLoc = static_cast<T*>(it->second);
            return true;
        }
        else
        {
            //Name mismatch: Give error
            std::cout<<"Load Error: Name mismatch '"<<s<<"'. - Something has been altered. Returning nullptr. \n"<<std::endl; //cannot guarentee safety of the pointer.
            *returnLoc = nullptr;
            return false;
        }
    }
    else
    {
        //if it doesnt exist, create it
        T* create = new T(s);
        if(create->correctlyLoaded)
        {
            //check loading process succeded
            internalMap.insert(std::pair<std::string, Store*>(s, create));
            create->internalName = s;
            *returnLoc = create;
            return true;
        }
        else
        {
            //if something goes wrong in loading, return indication of failure
            delete create;
            //set returnLoc to point to default or just nullptr it?
            //Loading incomplete: Give error
            std::cout<<"Load Error: Cannot load object '"<<s<<"'. Returning nullptr. \n"<<std::endl; //Loading a new object hasnt worked - report it
            *returnLoc = nullptr;
            return false;
        }
    }
}

template <typename T>
class Unload
{
public:
    //scene
    static bool Object(T** deletePtr);//objects
};

//IMPLEMENTATION - needs to be moved and the acceptable classes controlled in .cpp
template <class T>
bool Unload<T>::Object(T** deletePtr)
{
    //Deleting is controlled by pointers
    std::map<std::string, Store*>::const_iterator it;
    std::string key = "";
    T* editablePtr;
    for (it = internalMap.begin(); it != internalMap.end(); ++it) //loop through to find the existing pointer
    {
        if (*deletePtr == static_cast<T*>(it->second))
        {
            key = it->first;
            editablePtr = static_cast<T*>(it->second);
            break;
        }
    }
    if(it != internalMap.end())
    {
        //if it exists edit values and return
        editablePtr->usageCount -=1;
        if(editablePtr->usageCount == 0 && key == editablePtr->internalName)
        {
            delete editablePtr;
            internalMap.erase(key);
            *deletePtr = nullptr;
            return true;
        }
        *deletePtr = nullptr;
        return true;
    }
    std::cout<<"Unload Error: Cannot locate object. Returning nullptr. \n"<<std::endl;
    *deletePtr = nullptr;
    return false;
}

#endif // LOADER_H_INCLUDED
