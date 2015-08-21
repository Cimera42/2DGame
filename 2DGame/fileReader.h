#ifndef FILEREADER_H_INCLUDED
#define FILEREADER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include "typeConversion.h"

class DataProperty
{
public:
    std::string propertyName;
    std::vector<std::string> values;
};

class DataElement
{
public:
    std::string elementName; ///The element type
    std::string elementIdentifier; ///An optional ID for the element
    std::vector<DataProperty*> properties;
};

template<typename T>
struct typeIdentity { typedef T type; };

class DataBlock ///The actual chunk passed to whatever function to then extract and use the properties of.
{
public:
    std::vector<DataElement*> elements; ///The elements within the block

    int elementIndex = -1;
    int propertyIndex = -1;
    //int valueIndex;
    bool getNextElement();
    bool checkCurrentElement(std::string elementNameT);
    bool getNextProperty();
    bool checkCurrentProperty(std::string propertyNameT);
    template <typename T> T getCurrentValue()
    {
        //this calls the private functions depending on type
        T value;
        if(elementIndex != -1 && propertyIndex != -1)
            value = getCurrentValue(typeIdentity<T>()); //http://stackoverflow.com/questions/3052579/explicit-specialization-in-non-namespace-scope
        return value;
    }
private:
    void resetElementIndex();
    void resetPropertyIndex();
    template<typename T> T getCurrentValue(typeIdentity<T>)
    {
        //get the current value through index's depending on the type
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0];
        return str;
    }
    bool getCurrentValue(typeIdentity<bool>)
    {
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0];
        return stringToBool(str);
    }
    float getCurrentValue(typeIdentity<float>)
    {
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0];
        return stringToFloat(str);
    }
    int getCurrentValue(typeIdentity<int>)
    {
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0];
        return stringToInt(str);
    }
    glm::vec2 getCurrentValue(typeIdentity<glm::vec2>)
    {
        std::string str1 = elements[elementIndex]->properties[propertyIndex]->values[0];
        std::string str2 = elements[elementIndex]->properties[propertyIndex]->values[1];
        glm::vec2 vec = glm::vec2(stringToFloat(str1), stringToFloat(str2));
        return vec;
    }
    glm::vec3 getCurrentValue(typeIdentity<glm::vec3>)
    {
        std::string str1 = elements[elementIndex]->properties[propertyIndex]->values[0];
        std::string str2 = elements[elementIndex]->properties[propertyIndex]->values[1];
        std::string str3 = elements[elementIndex]->properties[propertyIndex]->values[2];
        glm::vec3 vec = glm::vec3(stringToFloat(str1), stringToFloat(str2), stringToFloat(str3));
        return vec;
    }
};

class File
{
public:
    std::string fileName; ///Name of the file
    std::fstream fileStream; ///Can be used to check if the current file is being accessed (is_open()) and also used as stream itself
    bool readOrWrite; ///Read = 0, Write = 1;
    bool success = true;///Assumed true, can write otherwise if errors

    int blockSize = 0;

    DataBlock* readFromFile(std::string fileName); ///Reads the file and put the contents into a DataBlock

private:
    bool ReadDataBlock(std::string block, DataBlock* datablock);///Used by readFromFile to extract datablock
    bool checkToken(std::string token);///Checks whether file symbols exist inside a string
    void checkExtractPos(int* a);///Used in ReadDataBlock to determine if the extracted position is < current position
    bool currentlyCommenting = false;///Used within ommition of comments
    std::string omitComments(std::string input); ///Returns a string with no comments

};

///Find ways to get template in cpp :)


#endif // FILEREADER_H_INCLUDED
