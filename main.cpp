#include <fstream>
#include <iostream>
#include <array>
#include <unordered_map>

#include <TextFileHandler.hpp>

#include "NameGenerators.hpp"
#include "PlanetSystemGenerator.hpp"

const std::array<char, 5> VOWELS {'a', 'e', 'i', 'o', 'u'};

const std::array<char, 21> CONSONANTS {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

// void output_planet_names()
// {
//     std::ofstream out_stream("PlanetNames.txt", std::ios::out);

//     for(int i = 0; i < 10; ++i) out_stream << NameGenerators::generate_planet_name() << '\n';

//     out_stream.close();
// }

void generate_planet_system()
{
    std::vector<Planet> planet_system = PlanetSystemGenerator::generate_planet_system(ROUTINE_OPERATION);

    std::ofstream out_stream("Planets.txt", std::ios::out);

    for(const Planet& planet : planet_system)
    {
        out_stream <<  "\nName: " << planet.name << "\nType: " << planet.planet_type_readable 
        << "\nSize: " << int(planet.size) << "\nDistance from Star: " << int(planet.distance_from_star) << "\n\n";
    }

    out_stream.close();
}

void generate_two_cluster()
{
    std::ofstream out_stream("TwoClusters.txt", std::ios::out);

    for(int i = 0; i < CONSONANTS.size(); ++i)
    {
        out_stream << "----\n";

        for(int j = 0; j < CONSONANTS.size(); ++j)
        {
            out_stream << 'a' << CONSONANTS.at(i) << CONSONANTS.at(j) << "a\n";
        }
    }

    out_stream.close(); 
}


int main()
{;
    TextFileHandler::clear_file("CrashLog.txt");
    NameGenerators::init();
    
    generate_planet_system();
    return 0;
}
