#ifndef SCENESTORE_H_INCLUDED
#define SCENESTORE_H_INCLUDED

#include "fileReader.h"
#include "store.h"

class SceneStore : public Store
{
public:
    SceneStore();//Default values set
    ~SceneStore(){};
    void loadStore(std::string); //Load the actual data on a new thread

    DataBlock* sceneBlock;
};

#endif // SCENESTORE_H_INCLUDED
