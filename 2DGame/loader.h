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
#include <pthread.h>

extern std::map<std::string, Store*> internalMap;


///Distribution Classes
template <class T>
class Load
{
private:
    static void *threadedLoad(void*);
public:
    //scene
    static bool Object(T** returnLoc, std::string s);//objects
};

template <class T>
class LoadJoin //Class to allow for paramter transfer to thread
{
public:
    T** returnLoc;
    std::string s;
};

template <class T>
void* Load<T>::threadedLoad(void* inptr)
{
    LoadJoin<T> inParam;
    inParam = *((LoadJoin<T>*) inptr);
    std::string s = inParam.s;
    std::cout << s <<" In Load"<< std::endl;
    T** returnLoc = inParam.returnLoc;

    //Loading is controlled by the string
    std::map<std::string, Store*>::iterator it = internalMap.find(s); //see if the object already exists
    if(it != internalMap.end())
    {
        //if it exists, double check name is correct,
        if(it->second->internalName == s)
        {
            //if the name matches (which it should unless its been altered, use this
            it->second->usageCount += 1;
            //use this and return
            *returnLoc = static_cast<T*>(it->second);
            return NULL; //true;
        }
        else
        {
            //Name mismatch: Give error
            std::cout<<"Load Error: Name mismatch '"<<s<<"'. - Something has been altered. Returning nullptr. \n \n"; //cannot guarentee safety of the pointer.
            //use default and return
            *returnLoc = nullptr;
            return NULL; //false;
        }
    }
    else
    {
        //if it doesnt exist, create it
        T* create = new T();
        create->loadStore(s);
        if(create->correctlyLoaded)
        {
            //check loading process succeded
            internalMap.insert(std::pair<std::string, Store*>(s, create));
            create->internalName = s;
            //overide and delete and return
            *returnLoc = create;
            return NULL; //true;
        }
        else
        {
            //if something goes wrong in loading, return indication of failure
            delete create;
            //set returnLoc to point to default or just nullptr it?
            //Loading incomplete: Give error
            std::cout<<"Load Error: Cannot load object '"<<s<<"'. Returning nullptr. \n \n"; //Loading a new object hasnt worked - report it
            //use default and delete the new threaded one etc etc and return
            *returnLoc = nullptr;
            return NULL; //false;
        }
    }
}

#include <GLFW/glfw3.h>
//IMPLEMENTATION - needs to be moved and the acceptable classes controlled in .cpp
template <class T>
bool Load<T>::Object(T** returnLoc, std::string s)
{
    //Create a new instance of the store
    T * create = new T();
    create->loadStore(s); //REMOVE IF 2ND THREAD
    create->internalName = s; //REMOVE IF 2ND THREAD
    *returnLoc = create;

    //Create paramters to send to secondary thread
    LoadJoin<T> param;
    param.returnLoc = returnLoc;
    param.s = s;

    //IF 2ND THREAD, REMOVE COMMENTS
    //Create a thread which does loading, and in the meantime - return the created instance of the store.
    //pthread_t thread;
    //pthread_create(&thread, NULL, threadedLoad, (void*) &param);
    //pthread_join(thread, NULL);

    return true;
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
    std::cout<<"Unload Error: Cannot locate object. Returning nullptr. \n \n";
    *deletePtr = nullptr;
    return false;
}

#endif // LOADER_H_INCLUDED
