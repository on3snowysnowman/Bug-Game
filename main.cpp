#include <iostream>

#include <JsonHandler.hpp>

#include "NameGenerators.hpp"


int main()
{
    json planet_names = json::array({});

    for(int i = 0; i < 30; ++i)
    {
        planet_names.push_back(NameGenerators::generate_planet_name());
    }

    JsonHandler::dump(planet_names, "PlanetNames.json");

    return 0;
}