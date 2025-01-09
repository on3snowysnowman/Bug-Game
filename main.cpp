#include <fstream>
#include <iostream>
#include <array>
#include <unordered_map>

#include <TextFileHandler.hpp>

#include "NameGenerators.hpp"

const std::array<char, 5> VOWELS {'a', 'e', 'i', 'o', 'u'};

const std::array<char, 21> CONSONANTS {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

void output_planet_names()
{
    std::ofstream out_stream("PlanetNames.txt", std::ios::out);

    for(int i = 0; i < 10; ++i) out_stream << NameGenerators::generate_planet_name() << '\n';

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

// If more than one consonant, check first letter 

int main()
{;
    TextFileHandler::clear_file("CrashLog.txt");
    // std::string temp;

    // std::ifstream in_stream("Out.txt");
    // std::ofstream out_stream("Netting.txt", std::ios::out);

    // while(std::getline(in_stream, temp))
    // {
    //     if(temp.at(0) != 'b') continue;

    //     std::string precursor = 'a' + temp.substr(0, 2);

    //     out_stream << "---\n";

    //     for(int i = 0; i < CONSONANTS.size(); ++i)
    //     {
    //         out_stream << precursor << CONSONANTS.at(i) << "a\n";
    //     }
    // }

    // in_stream.close();
    // out_stream.close();
    NameGenerators::init();

    output_planet_names();

    // std::unordered_map<std::string, int> results;

    // for(int i = 0; i < 100; ++i)
    // {
    //     ++results[NameGenerators::generate_planet_name()];
    // }

    // for(const auto _pair : results)
    // {
    //     if(_pair.second == 1) continue;

    //     std::cout << _pair.first << ": " << _pair.second << "\n";
    // }

    
    return 0;
}
