#ifndef SCENESTORE_H_INCLUDED
#define SCENESTORE_H_INCLUDED

#include "fileReader.h"
#include "store.h"

class SceneStore : public Store
{
public:
    SceneStore(std::string);
    ~SceneStore(){};

    DataBlock* sceneBlock;
    int amountOfElements;
};

#endif // SCENESTORE_H_INCLUDED
