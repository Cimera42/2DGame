#ifndef FILEREADER_H_INCLUDED
#define FILEREADER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>

class DataProperty
{
public:
    std::string propertyName;
    std::vector<std::string> values; //figure out a way to template a variable
};

class DataElement
{
public:
    std::string elementName; ///The element type
    std::string elementIdentifier; ///An optional ID for the element
    std::vector<DataProperty*> properties;
};

class DataBlock ///The actual chunk passed to whatever function to then extract and use the properties of.
{
public:
    std::vector<DataElement*> elements;
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

#endif // FILEREADER_H_INCLUDED
