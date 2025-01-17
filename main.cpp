#include <iostream>
#include <map>

#include <TextFileHandler.hpp>
#include <JsonHandler.hpp>

#include "Simulator.hpp"

int main()
{
    TextFileHandler::clear_file("CrashLog.txt");

    // WeightedDistribution<int, 4> wd ({1, 2, 3, 4}, {1, 1, 1, 1});

    // std::map<int, int> results;
 
    // const int TRIALS = 100000;

    // for(int i = 0; i < TRIALS; ++i)
    // {
    //     ++results[wd.sample()];
    // }

    // for(auto _pair : results)
    // {
    //     std::cout << _pair.first << ": " << (_pair.second / (1.0 * TRIALS)) * 100 << "%\n";
    // }

    Simulator simulator;

    simulator.start();
    return 0;
}
