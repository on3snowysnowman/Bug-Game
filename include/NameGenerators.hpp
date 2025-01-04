/**
 * @file NameGenerators.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 01-03-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <string>
#include <array>

#include <Fr_WeightedDistribution.hpp>

/** Static class used for generating random names for various different entities. */
class NameGenerators
{

public:

    static std::string generate_player_name();

    static std::string generate_planet_name();

private:

    static WeightedDistribution<std::string, 24> consonants_weighted_distribution;
    static WeightedDistribution<std::string, 11> vowels_weighted_distribution;
};

