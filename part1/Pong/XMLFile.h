
#pragma once

#include "MajorInclude.h"

class XmlFile
{
    std::vector<tinyxml2::XMLNode*> nodes;
    unsigned int currentNodeID;
    tinyxml2::XMLDocument file;
public:
    XmlFile(std::string str, std::string node);
    XmlFile(std::string str);
    ~XmlFile();

    bool next();

    void setNode(std::string nodeName);
    void back();

    std::string getValue(std::string nodeValueID);
};
