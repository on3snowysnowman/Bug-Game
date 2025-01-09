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
#include <fstream>

#include <Fr_Random.hpp>
#include <Fr_Math.hpp>

#include "NameGenerators.hpp"


// Static Members

const std::string NameGenerators::s_TWO_CONSONANT_CLUSTER_NO_END_VOWEL_REQUIRED_PATH = 
    "data/name_generation/TwoConsonantClusterNoEndVowelRequired.txt";
const std::string NameGenerators::s_TWO_CONSONANT_CLUSTER_END_VOWEL_REQUIRED_PATH =
    "data/name_generation/TwoConsonantClusterEndVowelRequired.txt";

const std::array<char, 5> NameGenerators::s_VOWELS {'a', 'e', 'i', 'o', 'u'};

const std::array<char, 21> NameGenerators::s_CONSONANTS {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

std::array<std::array<char, 2>, 171> NameGenerators::s_two_consonant_cluster_no_end_vowel_required;

std::array<std::array<char, 2>, 269> NameGenerators::s_two_consonant_cluster_end_vowel_required;

const WeightedDistribution<uint8_t, 2> NameGenerators::s_NUM_CONSONANT_OPTIONS({1, 2}, {2, 2000});



// Public

void NameGenerators::init()
{
    _load_two_consonant_clusters();
}

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
    std::string planet_name;

    bool vowel_next = FrostRandom::get_random_int(0, 1);

    uint8_t character_budget = FrostRandom::get_random_int(3, 9);

    if(vowel_next)
    {
        _handle_vowel_query(planet_name, character_budget);
        vowel_next = false;
    }

    else
    {
        planet_name.push_back(s_CONSONANTS.at(
            FrostRandom::get_random_int(0, s_CONSONANTS.size() - 1)));
        vowel_next = true;
        --character_budget;
    }

    while(character_budget > 0)
    {
        // If a vowel needs to be generated. 
        if(vowel_next)
        {
            _handle_vowel_query(planet_name, character_budget);
            vowel_next = false;
            continue;
        } 

        // A consonant needs to be generated.
        
        _handle_consonant_query(planet_name, character_budget);
        vowel_next = true;
    }

    // Capitalize the first character.
    planet_name.at(0) -= 32;

    return planet_name;
}

// Private

void NameGenerators::_load_two_consonant_clusters()
{
    // Handle consonant clusters of size 2 that don't require a vowel.

    std::ifstream in_stream(s_TWO_CONSONANT_CLUSTER_NO_END_VOWEL_REQUIRED_PATH);

    if(!in_stream.is_open())
    {
        TextFileHandler::add_to_buffer("[ERR] _load_two_consonant_clusters() -> Failed to open "
            "file: " + s_TWO_CONSONANT_CLUSTER_NO_END_VOWEL_REQUIRED_PATH + '\n');
        TextFileHandler::write("CrashLog.txt", Frost::APPEND);
        exit(1);
    }

    // Fetch the contents of the file and place them in a string.
    std::string file_content(
        (std::istreambuf_iterator<char>(in_stream)), std::istreambuf_iterator<char>());
    

    for(int i = 0; i < (s_two_consonant_cluster_no_end_vowel_required.size() * 2) - 1; i += 2)
    {
        // Fetch the specific two consonant cluster from the file content.
        s_two_consonant_cluster_no_end_vowel_required.at(i / 2).at(0) = file_content.at(i);
        s_two_consonant_cluster_no_end_vowel_required.at(i / 2).at(1) = file_content.at(i + 1);
    }

    in_stream.close();

    // Handle consonant clusters of size 2 that require a vowel.

    in_stream.open(s_TWO_CONSONANT_CLUSTER_END_VOWEL_REQUIRED_PATH);

    if(!in_stream.is_open())
    {
        TextFileHandler::add_to_buffer("[ERR] _load_two_consonant_clusters() -> Failed to open "
            "file: " + s_TWO_CONSONANT_CLUSTER_END_VOWEL_REQUIRED_PATH + '\n');
        TextFileHandler::write("CrashLog.txt", Frost::APPEND);
        exit(1);
    }

    // Fetch the contents of the file and place them in the string.
    file_content = std::string(
        (std::istreambuf_iterator<char>(in_stream)), std::istreambuf_iterator<char>());

    for(int i = 0; i < (s_two_consonant_cluster_end_vowel_required.size() * 2) - 1; i += 2)
    {
        // Fetch the specific two consonant cluster from the file content.
        s_two_consonant_cluster_end_vowel_required.at(i / 2).at(0) = file_content.at(i);
        s_two_consonant_cluster_end_vowel_required.at(i / 2).at(1) = file_content.at(i + 1);
    }

    in_stream.close();
}

void NameGenerators::_handle_vowel_query(std::string& content, uint8_t& character_budget)
{
    // Generate vowel cluster if the character budget allows it. 25%.
    if(character_budget >= 2 && FrostRandom::get_random_int(1, 4) == 1)
    {
        content.push_back(s_VOWELS.at(FrostRandom::get_random_int(0, s_VOWELS.size() - 1)));
        content.push_back(s_VOWELS.at(FrostRandom::get_random_int(0, s_VOWELS.size() - 1)));

        character_budget -= 2;
        return;
    }

    // Generate single vowel.
    content.push_back(s_VOWELS.at(FrostRandom::get_random_int(0, s_VOWELS.size() - 1)));
    --character_budget;
}

void NameGenerators::_handle_consonant_query(std::string& content, uint8_t& character_budget)
{
    if(character_budget == 1) 
    {
        content.push_back(s_CONSONANTS.at(FrostRandom::get_random_int(0, s_CONSONANTS.size() - 1)));
        --character_budget;
        return;
    }

    if(character_budget == 2)
    {
        if(s_NUM_CONSONANT_OPTIONS.sample() == 2)
        {
            int rand_num = FrostRandom::get_random_int(0, 
                s_two_consonant_cluster_no_end_vowel_required.size() - 1);
            
            content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(0));
            content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(1));
            character_budget -= 2;
            return;
        }

        content.push_back(s_CONSONANTS.at(FrostRandom::get_random_int(0, s_CONSONANTS.size() - 1)));
        --character_budget;
        return;
    }

    // Character budget is greater than 2.

    if(s_NUM_CONSONANT_OPTIONS.sample() == 2)
    {
        if(FrostRandom::get_random_int(7, 11) <= 7)
        {
            int rand_num = FrostRandom::get_random_int(0, 
                s_two_consonant_cluster_end_vowel_required.size() - 1);
            
            content.push_back(s_two_consonant_cluster_end_vowel_required.at(rand_num).at(0));
            content.push_back(s_two_consonant_cluster_end_vowel_required.at(rand_num).at(1));
            character_budget -= 2;
            return;
        }

        int rand_num = FrostRandom::get_random_int(0, 
            s_two_consonant_cluster_no_end_vowel_required.size() - 1);
        
        content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(0));
        content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(1));
        character_budget -= 2;
        return;
    }

    content.push_back(s_CONSONANTS.at(FrostRandom::get_random_int(0, s_CONSONANTS.size() - 1)));
    --character_budget;
    return;


    // uint8_t maximum_generatable_consonants = character_budget;
    // maximum_generatable_consonants = 
    //     Frost::clamp_uint8_to_maximum(maximum_generatable_consonants, 3);

    // int rand_num;    

    // switch(s_NUM_CONSONANT_OPTIONS.sample(0, maximum_generatable_consonants - 1))
    // {
    //     // Add single consonant.
    //     case 0:

    //         content.push_back(s_CONSONANTS.at(FrostRandom::get_random_int(0, s_CONSONANTS.size() - 1)));
    //         --character_budget;
    //         break;

    //     // Add two cluster consonant with no vowel ending required.
    //     case 1:

    //         rand_num = FrostRandom::get_random_int(0, s_two_consonant_cluster_no_end_vowel_required.size() - 1);

    //         content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(0));
    //         content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(1));
    //         --character_budget;
    //         break;

    //     // Add either two cluster consonant with end vowel required or a three consonant cluster
    //     // with no vowel ending required.
    //     case 2:



    //         break;

    //     case 
    // }
    
    
}
