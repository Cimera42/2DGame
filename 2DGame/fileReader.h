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
    std::string getCurrentIdentifier();
    bool getNextProperty();
    bool checkCurrentProperty(std::string propertyNameT);
    template <typename T> T getCurrentValue(int offset)
    {
        //this calls the private functions depending on type
        T value;
        if(elementIndex != -1 && propertyIndex != -1)
            value = getCurrentValue(typeIdentity<T>(),offset); //http://stackoverflow.com/questions/3052579/explicit-specialization-in-non-namespace-scope
        return value;
    }
private:
    void resetElementIndex();
    void resetPropertyIndex();
    template<typename T> T getCurrentValue(typeIdentity<T>,int offset)
    {
        //get the current value through index's depending on the type
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        return str;
    }
    bool getCurrentValue(typeIdentity<bool>,int offset)
    {
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        return stringToBool(str);
    }
    float getCurrentValue(typeIdentity<float>,int offset)
    {
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        return stringToFloat(str);
    }
    int getCurrentValue(typeIdentity<int>,int offset)
    {
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        return stringToInt(str);
    }
    char getCurrentValue(typeIdentity<char>,int offset)
    {
        std::string str = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        return str.c_str()[0];
    }
    glm::vec2 getCurrentValue(typeIdentity<glm::vec2>,int offset)
    {
        std::string str1 = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        std::string str2 = elements[elementIndex]->properties[propertyIndex]->values[1+offset];
        glm::vec2 vec = glm::vec2(stringToFloat(str1), stringToFloat(str2));
        return vec;
    }
    glm::vec3 getCurrentValue(typeIdentity<glm::vec3>,int offset)
    {
        std::string str1 = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        std::string str2 = elements[elementIndex]->properties[propertyIndex]->values[1+offset];
        std::string str3 = elements[elementIndex]->properties[propertyIndex]->values[2+offset];
        glm::vec3 vec = glm::vec3(stringToFloat(str1), stringToFloat(str2), stringToFloat(str3));
        return vec;
    }
    glm::vec4 getCurrentValue(typeIdentity<glm::vec4>,int offset)
    {
        std::string str1 = elements[elementIndex]->properties[propertyIndex]->values[0+offset];
        std::string str2 = elements[elementIndex]->properties[propertyIndex]->values[1+offset];
        std::string str3 = elements[elementIndex]->properties[propertyIndex]->values[2+offset];
        std::string str4 = elements[elementIndex]->properties[propertyIndex]->values[3+offset];
        glm::vec4 vec = glm::vec4(stringToFloat(str1), stringToFloat(str2), stringToFloat(str3), stringToFloat(str4));
        return vec;
    }
};

class File
{
public:
    std::string fileName; ///Name of the file
    std::string fileDirectory; ///The directory of the file
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
    bool currentlyWhitespacing = false;///Used within ommition of whitespace
    std::string omitComments(std::string input); ///Returns a string with no comments
    std::string omitWhitespace(std::string input); ///Returns a string with only whitespace in values

};

///Find ways to get template in cpp :)


#endif // FILEREADER_H_INCLUDED
