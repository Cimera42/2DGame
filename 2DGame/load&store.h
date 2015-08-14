#ifndef LOAD&STORE_H_INCLUDED
#define LOAD&STORE_H_INCLUDED

#include <map>
#include <string>
#include <iostream>
#include "fileReader.h"

//Holds the base object class
class BaseStore
{
    template <class T> friend class Load;
    template <class T> friend class Unload;
public:
    BaseStore() { usageCount+=1; }; //Each new object increases usageCount
    virtual ~BaseStore(){};

protected:
    //Prevent usage outside of the class, subclass and friends
    int usageCount = 0; //! Used as an internal counter.
    bool correctlyLoaded = false; //! Used to signify if the object has been loaded correctly. If not the object will be immediately deleted. (Save guard)
    std::string internalName; //! Used as a check on the object that's been loaded and maintained
};

class SceneStore : public BaseStore
{
public:
    SceneStore(std::string);
    ~SceneStore(){};

    DataBlock* sceneBlock;
    int amountOfElements;
};

class TextureStore : public BaseStore
{
public:
    TextureStore(std::string);
    ~TextureStore(){};

    //GLuint textureID;
};


extern std::map<std::string, BaseStore*> internalMap;
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
    std::map<std::string, BaseStore*>::iterator it = internalMap.find(s); //see if the object already exists
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
            std::cout<<"Load Error: Name mismatch '"<<s<<"'. - Something has been altered. Returning nullptr."<<std::endl; //cannot guarentee safety of the pointer.
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
            internalMap.insert(std::pair<std::string, BaseStore*>(s, create));
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
            std::cout<<"Load Error: Cannot load object '"<<s<<"'. Returning nullptr."<<std::endl; //Loading a new object hasnt worked - report it
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
    std::map<std::string, BaseStore*>::const_iterator it;
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
     std::cout<<"Unload Error: Cannot locate object. Returning nullptr."<<std::endl;
    *deletePtr = nullptr;
    return false;
}

///TODO:
/*
- Use smart pointers... (aparently you cannot delete a pointer that you do not assign through new :O )
- Control the use of the string independantly within each of the subStores
- Make a version of loading so as if you dont care about what model something is using and u only care with what ur being pointed to?
- Find a way to put implementations of templates in .cpp
*/


#endif // LOAD&STORE_H_INCLUDED
