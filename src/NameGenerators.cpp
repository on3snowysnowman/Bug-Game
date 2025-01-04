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
#include "JsonHandler.hpp"


// Static Members

WeightedDistribution<std::string, 24> NameGenerators::consonants_weighted_distribution(
    {"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", 
    "y", "z", "th", "sh", "ch"}, 
    {20, 20, 20, 10, 10, 10, 5, 10, 10, 15, 15, 10, 5, 3, 20, 20, 10, 5, 3, 3, 3, 20, 20, 20});

WeightedDistribution<std::string, 11> NameGenerators::vowels_weighted_distribution(
    {"a", "e", "i", "o", "u", "ae", "ai", "eo", "ia", "ou", "ua"},
    {10, 10, 10, 10, 10, 10, 5, 5, 5, 5, 5});

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
    // TODO: Rewrite this sub par function.

    const int NUM_CONSONANTS = consonants_weighted_distribution.size();
    const int NUM_VOWELS = vowels_weighted_distribution.size();

    // Determine random lengths for the name (between 1 and 3 syllables)
    int num_syllables = FrostRandom::get_random_int(1, 3);
    
    std::string name;
    bool start_with_vowel = FrostRandom::get_random_int(0, 1);

    if(start_with_vowel)
    {
        for (int i = 0; i < num_syllables; ++i) 
        {

        name += consonants_weighted_distribution.sample() + vowels_weighted_distribution.sample();
        }
    }

    else
    {
        for (int i = 0; i < num_syllables; ++i) 
        {
            name += vowels_weighted_distribution.sample() + consonants_weighted_distribution.sample();
        }
    }

    // Randomly add a suffix
    if(FrostRandom::get_random_int(0, 1))
    {
        const std::array<std::string, 7> SUFFIXES {"on", "ar", "us", "ia", "um", "is", "os"};
        name += SUFFIXES.at(FrostRandom::get_random_int(0, SUFFIXES.size() - 1));
    }
    
    // If no suffix was added and there was only 1 syllable in the word, add another syllable. 
    else if(num_syllables == 1)
    {
        if(start_with_vowel) name += vowels_weighted_distribution.sample();
        // else name += consonants_weighted_distribution.sample();
    }

    // Capitalize the first letter of the name
    name[0] = std::toupper(name[0]);

    return name;
}

// Private


