/**
 * @file NameGenerators.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 01-03-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <ctime>
#include <iostream>

#include <Fr_Random.hpp>

#include "NameGenerators.hpp"


// Static Members

const std::array<std::string, 24> NameGenerators::CONSONANTS {"b", "c", "d", "f", "g", "h", "j", 
    "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "y", "z", "th", "sh", "ch"};

const std::array<std::string, 11> NameGenerators::VOWELS
    {"a", "e", "i", "o", "u", "ae", "ai", "eo", "ia", "ou", "ua"};

// Public

std::string NameGenerators::generate_player_name()
{
    const std::array<char, 8> FIRST_CHARS
        {'A', 'T', 'O', 'R', 'U', 'I', 'O', 'S'};
    const std::array<char, 8> SECOND_CHARS
        {'E', 'D', 'F', 'K', 'L', 'C', 'V', 'B'};

    std::string player_name; 

    player_name.push_back(FIRST_CHARS.at(FrostRandom::get_random_int(0, FIRST_CHARS.size() - 1)));
    player_name.push_back(char(FrostRandom::get_random_int(48, 57)));
    player_name.append(" - ");
    player_name.push_back(SECOND_CHARS.at(
        FrostRandom::get_random_int(0, SECOND_CHARS.size() - 1)));
    player_name.push_back(char(FrostRandom::get_random_int(48, 57)));
    player_name.push_back(char(FrostRandom::get_random_int(48, 57)));

    return player_name;
}

std::string NameGenerators::generate_planet_name()
{
    // Seed random number generator
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        seeded = true;
    }

    const int NUM_CONSONANTS = CONSONANTS.size();
    const int NUM_VOWELS = VOWELS.size();

    // Determine random lengths for the name (between 1 and 3 syllables)
    int num_syllables = FrostRandom::get_random_int(1, 3);
    
    std::string name;

    for (int i = 0; i < num_syllables; ++i) {

        // Append to the name
        name +=
            CONSONANTS.at(FrostRandom::get_random_int(0, NUM_CONSONANTS - 1)) + 
            VOWELS.at(FrostRandom::get_random_int(0, NUM_VOWELS - 1));
    }

    // Randomly add a suffix
    if(FrostRandom::get_random_int(0, 1))
    {
        const std::array<std::string, 7> SUFFIXES {"on", "ar", "us", "ia", "um", "is", "os"};
        name += SUFFIXES.at(FrostRandom::get_random_int(0, SUFFIXES.size() - 1));
    }
    
    // If no suffix was added, add another consonant if there is only 1 syllable in the word, 
    // otherwise, randomly add another syllable.
    else if(num_syllables == 1 || FrostRandom::get_random_int(0, 1))
    {
        name += CONSONANTS.at(FrostRandom::get_random_int(0, NUM_CONSONANTS - 1));
    }

    // Capitalize the first letter of the name
    name[0] = std::toupper(name[0]);

    return name;
}

// Private


