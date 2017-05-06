
#include "XMLFile.h"
#include "Exception.h"

XmlFile::XmlFile(std::string str)
    : currentNodeID(-1)
{
    file.LoadFile(str.c_str());
}

XmlFile::XmlFile(std::string str, std::string node)
    : currentNodeID(-1)
{
    file.LoadFile(str.c_str());
    setNode(node);
}

XmlFile::~XmlFile()
{
}

void XmlFile::setNode(std::string str)
{
    tinyxml2::XMLNode * node;

    if (currentNodeID == -1)
    {
        node = file.FirstChildElement(str.c_str());
    }
    else
    {
        node = nodes[currentNodeID]->FirstChildElement(str.c_str());
    }

    if (node != nullptr)
    {
        ++currentNodeID;

        nodes.push_back(node);
    }
    else
    {
        throw Error(FILE_IO, "couldnt find node " + str, WILLIAM);
    }
}

std::string XmlFile::getValue(std::string str)
{
    std::string data = "";

    try
    {
        tinyxml2::XMLElement * node = nodes[currentNodeID]->FirstChildElement(str.c_str());

        if (node == NULL)
        {
            throw Error(FILE_IO, "couldnt retrieve xml node", WILLIAM);
        }
        else
        {
            data = node->GetText();
        }
    }
    catch (...)
    {
        throw Error(FILE_IO, "couldnt grab xml node", WILLIAM);
    }

    return data;
}

void XmlFile::back()
{
    nodes.pop_back();
    currentNodeID--;
}

bool XmlFile::next()
{
    tinyxml2::XMLNode * next = nodes[currentNodeID]->NextSibling();

    if (next == nullptr)
    {
        throw Error(FILE_IO, "Couldnt grab next xml node", WILLIAM);
    }
    else
    {
        nodes[currentNodeID] = next;
        return true;
    }
}
