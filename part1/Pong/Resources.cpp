
#include "Resources.h"

StatisticsFile::StatisticsFile()
    : file(filename, "stats")
{
    read();
}

StatisticsFile::~StatisticsFile()
{
    write();
}

void StatisticsFile::write()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* bounces = doc.NewElement("bounces");
    tinyxml2::XMLElement* stats = doc.NewElement("stats");
    tinyxml2::XMLElement* times = doc.NewElement("times");

    bounces->InsertEndChild(doc.NewText(to_string(data.bounces).c_str()));
    times->InsertEndChild(doc.NewText(to_string(data.times).c_str()));
    stats->InsertEndChild(bounces);
    stats->InsertEndChild(times);

    doc.InsertFirstChild(stats);
    doc.SaveFile("data/statistics.xml");
}

StatisticsData& StatisticsFile::getData()
{
    return(data);
}

void StatisticsFile::read()
{
    data.bounces = atoi(file.getValue("bounces").c_str());
    data.times = atoi(file.getValue("times").c_str());
}
