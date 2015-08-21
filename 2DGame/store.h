#ifndef STORE_H_INCLUDED
#define STORE_H_INCLUDED

#include <string>
#include <iostream>

//Holds the base object class
class Store
{
    template <class T> friend class Load;
    template <class T> friend class Unload;
public:
    Store(); ///Set the default values
    virtual ~Store();
    virtual void loadStore(std::string); ///Load the actual data on a new thread

protected:
    //Prevent usage outside of the class, subclass and friends
    int usageCount = 0; //! Used as an internal counter.
    bool correctlyLoaded = false; //! Used to signify if the object has been loaded correctly. If not the object will be immediately deleted. (Save guard)
    std::string internalName; //! Used as a check on the object that's been loaded and maintained
};

#endif // STORE_H_INCLUDED
