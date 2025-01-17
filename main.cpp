#include <iostream>
#include <map>

#include <TextFileHandler.hpp>
#include <JsonHandler.hpp>
#include <Fr_WeightedDistribution.hpp>

#include "Simulator.hpp"


int main()
{
    TextFileHandler::clear_file("CrashLog.txt");
    
    Simulator simulator;

    simulator.start();
    
    return 0;
}
