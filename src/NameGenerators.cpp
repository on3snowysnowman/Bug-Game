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
const std::string NameGenerators::s_TWO_CONSONANT_CLUSTER_STARTERS_PATH = 
    "data/name_generation/TwoConsonantClusterStarters.txt";

const std::array<char, 5> NameGenerators::s_VOWELS {'a', 'e', 'i', 'o', 'u'};

const std::array<char, 21> NameGenerators::s_CONSONANTS {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

std::array<std::array<char, 2>, 172> NameGenerators::s_two_consonant_cluster_no_end_vowel_required;

std::array<std::array<char, 2>, 268> NameGenerators::s_two_consonant_cluster_end_vowel_required;

std::array<std::array<char, 2>, 83> NameGenerators::s_two_consonant_cluster_starters;



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

    player_name.push_back(FIRST_CHARS.at(FrostRandom::get_random_num<uint8_t>(0, FIRST_CHARS.size() - 1)));
    player_name.push_back(char(FrostRandom::get_random_num<uint8_t>(48, 57)));
    player_name.append(" - ");
    player_name.push_back(SECOND_CHARS.at(
        FrostRandom::get_random_num<uint8_t>(0, SECOND_CHARS.size() - 1)));
    player_name.push_back(char(FrostRandom::get_random_num<uint8_t>(48, 57)));
    player_name.push_back(char(FrostRandom::get_random_num<uint8_t>(48, 57)));

    return player_name;
}
#include <iostream>
std::string NameGenerators::generate_planet_name()
{
    static uint8_t num {96};

    if(++num > 122) num = 96;

    std::string planet_name;

    bool vowel_next = FrostRandom::get_random_num<uint8_t>(0, 1);

    uint8_t character_budget = FrostRandom::get_random_num<uint8_t>(3, 9);

    // Handle the first character(s) being generated. For vowels, there is no behavior change,
    // however some consonant clusters don't work being placed at the beginning of the word, so a
    // separate array and function has been created for that.

    if(vowel_next)
    {
        _handle_vowel_query(planet_name, character_budget);
        vowel_next = false;
    }

    else
    {
        _handle_first_query_for_consonant(planet_name, character_budget);
        vowel_next = true;
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
    // Handle loading consonant clusters of size 2 that don't require a vowel.

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

    // Handle loading consonant clusters of size 2 that require a vowel.

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

    // Handle consonant cluster of size 2 that can start a word.

    in_stream.open(s_TWO_CONSONANT_CLUSTER_STARTERS_PATH);

    if(!in_stream.is_open())
    {
        TextFileHandler::add_to_buffer("[ERR] _load_two_consonant_clusters() -> Failed to open "
            "file: " + s_TWO_CONSONANT_CLUSTER_STARTERS_PATH + '\n');
        TextFileHandler::write("CrashLog.txt", Frost::APPEND);
        exit(1);
    }

    // Fetch the contents of the file and place them in the string.
    file_content = std::string(
        (std::istreambuf_iterator<char>(in_stream)), std::istreambuf_iterator<char>());

    for(int i = 0; i < (s_two_consonant_cluster_starters.size() * 2) - 1; i += 2)
    {
        // Fetch the specific two consonant cluster from the file content.
        s_two_consonant_cluster_starters.at(i / 2).at(0) = file_content.at(i);
        s_two_consonant_cluster_starters.at(i / 2).at(1) = file_content.at(i + 1);
    }

    in_stream.close();
}

void NameGenerators::_handle_first_query_for_consonant(std::string& content, uint8_t& character_budget)
{
    /**
     * Values:
     * 
     * 0: Single cluster
     * 1: Two cluster, no end vowel required
     * 2: Two cluster, end vowel required
     * 3: Three cluster, no end vowel required
     * 4: Three cluster, end vowel required
     */
    static WeightedDistribution<uint8_t, 3> cluster_options({0, 1, 2}, {7, 3, 1});

    if(character_budget == 3) cluster_options.set_weights<std::initializer_list<uint8_t>>({7, 3, 0}); 

    static uint8_t last_handled_budget {};
    // Since this is the first query of the generation, it is known that the character budget is 
    // guaranteed to be atleast 3.

    int rand_num;

    switch(cluster_options.sample())
    {
        // Single consonant.
        case 0:

            rand_num = FrostRandom::get_random_num<uint8_t>(0, s_CONSONANTS.size() - 1);
            content.push_back(s_CONSONANTS.at(rand_num));
            --character_budget;
            return;

        // Two cluster starter.
        case 1:

            rand_num = FrostRandom::get_random_num<uint8_t>(0, s_two_consonant_cluster_starters.size() - 1);
            content.push_back(s_two_consonant_cluster_starters.at(rand_num).at(0));
            content.push_back(s_two_consonant_cluster_starters.at(rand_num).at(1));
            character_budget -= 2;
            return;

        // Three cluster starter
        case 2:
            
            // character_budget -= 3;
            return;
    }
}

void NameGenerators::_handle_vowel_query(std::string& content, uint8_t& character_budget)
{
    // Generate vowel cluster if the character budget allows it. 25%.
    if(character_budget >= 2 && FrostRandom::get_random_num<uint8_t>(1, 4) == 1)
    {
        content.push_back(s_VOWELS.at(FrostRandom::get_random_num<uint8_t>(0, s_VOWELS.size() - 1)));
        content.push_back(s_VOWELS.at(FrostRandom::get_random_num<uint8_t>(0, s_VOWELS.size() - 1)));

        character_budget -= 2;
        return;
    }

    // Generate single vowel.
    content.push_back(s_VOWELS.at(FrostRandom::get_random_num<uint8_t>(0, s_VOWELS.size() - 1)));
    --character_budget;
}

void NameGenerators::_handle_consonant_query(std::string& content, uint8_t& character_budget)
{
    /**
     * Values:
     * 
     * 0: Single cluster
     * 1: Two cluster, no end vowel required
     * 2: Two cluster, end vowel required
     * 3: Three cluster, no end vowel required
     * 4: Three cluster, end vowel required
     */

    static WeightedDistribution<int, 5> cluster_options({0, 1, 2, 3, 4}, {7, 3, 1, 0, 0});

    static uint8_t last_handled_budget {};

    if(character_budget < 4 && last_handled_budget != character_budget)
    {
        if(character_budget < 2) cluster_options.set_weights<std::initializer_list<uint8_t>>({1, 0, 0, 0, 0});
        else if(character_budget < 3) cluster_options.set_weights<std::initializer_list<uint8_t>>({7, 3, 0, 0, 0});
        else cluster_options.set_weights<std::initializer_list<uint8_t>>({7, 3, 1, 0, 0});

        last_handled_budget = character_budget;
    }

    int rand_num;

    switch(cluster_options.sample())
    {
        // Single consonant.
        case 0:

            rand_num = FrostRandom::get_random_num<uint8_t>(0, s_CONSONANTS.size() - 1);
            content.push_back(s_CONSONANTS.at(rand_num));
            --character_budget;
            return;

        // Two cluster, no end vowel.
        case 1:

            rand_num = FrostRandom::get_random_num<uint16_t>(0, s_two_consonant_cluster_no_end_vowel_required.size() - 1);
            content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(0));
            content.push_back(s_two_consonant_cluster_no_end_vowel_required.at(rand_num).at(1));
            character_budget -= 2;
            return;

        // Two cluster, end vowel required.
        case 2:

            rand_num = FrostRandom::get_random_num<uint16_t>(0, s_two_consonant_cluster_end_vowel_required.size() - 1);
            content.push_back(s_two_consonant_cluster_end_vowel_required.at(rand_num).at(0));
            content.push_back(s_two_consonant_cluster_end_vowel_required.at(rand_num).at(1));
            character_budget -= 2;
            return;

        // Three cluster, no end vowel required.
        case 3:

            return;
    
        // Three cluster, end vowel required.
        case 4: 

            return;
    }
}
