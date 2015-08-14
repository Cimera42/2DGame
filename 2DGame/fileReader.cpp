#include "fileReader.h"

#include <iostream>

///Purpose is to extract properties under a common token layout within a non-binary format
///These properties will be checked against a set for different loadTypes.
/** Eg. - Same layout style as .css

(input: file name: scene1.txt)
Header contains basic data such as time & date editted, element count etc.?

_ElementToken_ _"_ _OptionalIDToken_ _"_
_{_
    _PropertyToken_ _:_ _ValueToken_ _;_
    _PropertyToken_ _:_ _ValueToken_ _,_ _ValueToken_ _;_
    _PropertyToken_ _:_ _ValueToken_ _;_
_}_

**/
/**
#define _ElementToken_ 0
#define _"_ 1
#define _OptionalIDToken_ 2
#define _{_ 3
#define _PropertyToken_ 4
#define _:_ 5
#define _ValueToken_ 6
#define _,_ 7
#define _;_ 8
#define _}_ 9
**/

///Also note: This should be able to parallel read files across multiple threads without affecting one another.

void File::checkExtractPos(int* a)
{
    if(*a < 0)
        *a = blockSize;
    return;
}

bool File::checkToken(std::string token)
{
    if (token.find('"') != std::string::npos)
        return false;
    if (token.find('{') != std::string::npos)
        return false;
    if (token.find(':') != std::string::npos)
        return false;
    if (token.find(',') != std::string::npos)
        return false;
    if (token.find(';') != std::string::npos)
        return false;
    if (token.find('}') != std::string::npos)
        return false;
    return true;
}

bool File::ReadDataBlock(std::string block, DataBlock* datablock)
{
    blockSize = block.size();
    int currentPos = 0;
    bool optionalToken = 0;
    int elementIndex = 0;
    int propertyIndex = 0;
    for(int i = 0; i <= 4; i++)//Why this is in a for loop I will never know
    {
        if(i == 0)
        {
            datablock->elements.push_back(new DataElement());
            //element token
            int extractPos1 = block.find_first_of('{', currentPos)-currentPos;
            int extractPos2 = block.find_first_of('"', currentPos)-currentPos;
            checkExtractPos(&extractPos1);
            checkExtractPos(&extractPos2);
            if(extractPos1<extractPos2)
            {
                std::string elementToken = block.substr(currentPos, extractPos1);
                if(!checkToken(elementToken))
                {
                    std::cout<<"Element contains incorrect syntax: \n"<<elementToken<<"\n"<<std::endl; //syntax error
                    return false;
                }
                datablock->elements[elementIndex]->elementName = elementToken;
                currentPos += extractPos1+1;
                optionalToken = false;
            }
            else if(extractPos2<extractPos1)
            {
                std::string elementToken = block.substr(currentPos, extractPos2);
                if(!checkToken(elementToken))
                {
                    std::cout<<"Element contains incorrect syntax: \n"<<elementToken<<"\n"<<std::endl; //syntax error
                    return false;
                }
                datablock->elements[elementIndex]->elementName = elementToken;
                currentPos += extractPos2+1;
                optionalToken = true;
            }
            else
            {
                std::cout<<"Element doesn't contain properties OR no terminating comment: \n"
                <<datablock->elements[elementIndex]->elementName<<" '"
                <<datablock->elements[elementIndex]->elementIdentifier<<"'\n"<<std::endl; //error
                return false;
            }
        }
        if(i == 1)
        {
            //check for optional
            if(optionalToken)
            {
                int extractPos1 = block.find_first_of('"', currentPos)-currentPos;
                int extractPos2 = block.find_first_of('{', currentPos)-currentPos;
                //first do the "
                std::string optionalTokenStr = block.substr(currentPos, extractPos1);
                if(!checkToken(optionalTokenStr))
                {
                    std::cout<<"Optional Identifier contains incorrect syntax: \n"
                    <<datablock->elements[elementIndex]->elementName<<" "<<optionalTokenStr<<"\n"<<std::endl; //syntax error
                    return false;
                }
                datablock->elements[elementIndex]->elementIdentifier = optionalTokenStr;
                currentPos += extractPos1+1;
                //then check if { is next, if not we have an issue
                if(block[currentPos] == '{')
                    currentPos++;
                else
                {
                    std::cout<<"Element doesn't contain properties (are you missing an '{' ?): \n"
                    <<datablock->elements[elementIndex]->elementName<<" '"
                    <<datablock->elements[elementIndex]->elementIdentifier<<"'\n"<<std::endl;
                    return false;
                }
            }
        }
        if(i == 2)
        {
            //break the properties section
            int first = currentPos;
            int last = block.find_first_of('}', currentPos);
            while(currentPos < last)//loop through all the properties
            {
                //create a new property
                datablock->elements[elementIndex]->properties.push_back(new DataProperty());
                int extractPos1 = block.find_first_of(':', currentPos)-currentPos;
                //do the propertyToken:
                std::string propertyToken = block.substr(currentPos, extractPos1);
                if(!checkToken(propertyToken))
                {
                    std::cout<<"Property contains incorrect syntax: \n"
                    <<datablock->elements[elementIndex]->elementName<<" '"
                    <<datablock->elements[elementIndex]->elementIdentifier<<"': \n"<<propertyToken<<"\n"<<std::endl; //syntax error
                    return false;
                }
                datablock->elements[elementIndex]->properties[propertyIndex]->propertyName = propertyToken;
                currentPos += extractPos1+1;
                //do the valueToken
                int innerLast = block.find_first_of(';', currentPos);
                while(currentPos < innerLast) //loop through all the values for a specific property
                {
                    //create a new value for a property
                    extractPos1 = block.find_first_of(',', currentPos)-currentPos;
                    int extractPos2 = block.find_first_of(';', currentPos)-currentPos;
                    checkExtractPos(&extractPos1);
                    if(extractPos1<extractPos2)
                    {
                        std::string valueToken = block.substr(currentPos, extractPos1);
                        if(!checkToken(valueToken))
                        {
                            std::cout<<"Value contains incorrect syntax: \n"
                            <<datablock->elements[elementIndex]->elementName<<" '"
                            <<datablock->elements[elementIndex]->elementIdentifier<<"': \n"
                            <<datablock->elements[elementIndex]->properties[propertyIndex]->propertyName<<": "<<valueToken<<"\n"<<std::endl; //syntax error;
                            return false;
                        }
                        datablock->elements[elementIndex]->properties[propertyIndex]->values.push_back(valueToken);
                        currentPos += extractPos1+1;
                    }
                    else if(extractPos2<extractPos1)
                    {
                        std::string valueToken = block.substr(currentPos, extractPos2);
                        if(!checkToken(valueToken))
                        {
                            std::cout<<"Value contains incorrect syntax: \n"
                            <<datablock->elements[elementIndex]->elementName<<" '"
                            <<datablock->elements[elementIndex]->elementIdentifier<<"': \n"
                            <<datablock->elements[elementIndex]->properties[propertyIndex]->propertyName<<": "<<valueToken<<"\n"<<std::endl; //syntax error;
                            return false;
                        }
                        datablock->elements[elementIndex]->properties[propertyIndex]->values.push_back(valueToken);
                        currentPos += extractPos2+1;
                    }
                    else
                        return false;
                }
                propertyIndex++;
            }
            currentPos+=1;
            elementIndex++;
        }
        if(i == 3)
        {
            if(currentPos >= block.size())
                continue;
            else
            {
                propertyIndex = 0;
                i = -1;
            }
        }
    }
    return true;
}

std::string File::omitComments(std::string input)
{
    std::string output;
    if(!currentlyCommenting)
    {
        //check if comment exists
        int commentPos = input.find("/*");
        if(commentPos != std::string::npos)
        {
            output += input.substr(0, commentPos);
            currentlyCommenting = true;
        }
        else
        {
            return input; //Safe to assume we can return input if no comment exists
        }
    }
    if(currentlyCommenting) //not else incase the comment is on the same word
    {
        //if we're in the middle of a comment, find the end or omit whole word
        int commentPos = input.find("*/");
        if(commentPos != std::string::npos)
        {
            output += input.substr(commentPos+2,input.size());
            currentlyCommenting = false;
        }
    }
    return output;
}

DataBlock* File::readFromFile(std::string name)
{
    readOrWrite = 0;
    fileName = name;
    fileStream.open(fileName.c_str(), std::fstream::in);//Tell we need to open to read
    if(fileStream.is_open()) //check if file opened
    {
        std::string word;
        std::string block;
        int maxSize = block.max_size();
        DataBlock* datablock = new DataBlock();
        //Add: getline - first line = header?
        while(fileStream >> word)//get all data to remove whitespace
        {
            //Do a check to determine if comments exist and get rid of them.
            word = omitComments(word);
            //Append word to blocks
            if(block.size()+word.size() > maxSize)
            {
                std::cout<<"STRING IS FULL - HOW?!?!!"<<std::endl;
                break;
            }
            block += word;
        }
        fileStream.close();
        if(ReadDataBlock(block, datablock))//Read the block string (no whitespace or comments) in datablock
        {
            success = true;
            return datablock;
        }
        delete datablock;
    }
    else
    {
        success = false;
        std::cout<<"Could not open file to read from: "<<fileName<<std::endl;
        return nullptr;
    }
    success = false;
    std::cout<<"Something went wrong when attempting to read from file: "<<fileName<<std::endl;
    return nullptr;
}