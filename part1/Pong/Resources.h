
#pragma once

#include "Framework.h"

#include <vector>
#include <string>

global_string filename = "data/statistics.xml";
global_string font = "data/MOZART_0.ttf";

struct StatisticsData
{
    int bounces;
    int times;
};

class StatisticsFile
{
    StatisticsData data;
    XmlFile file;
public:
    StatisticsFile();
    ~StatisticsFile();

    StatisticsData& getData();

    void write();
    void read();
};
