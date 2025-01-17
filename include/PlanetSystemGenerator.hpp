/**
 * @file PlanetSystemGenerator.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single class declaration.
 * @version 0.1
 * @date 01-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <vector>

#include <Fr_WeightedDistribution.hpp>

#include "Planet.hpp"
#include "GameDifficulty.hpp"
#include "Json.hpp"


/** Static class that generates procedural planet populated systems. */
class PlanetSystemGenerator
{

public:

    /** Sets the weights for the planet generation to a new list of weights. */
    static void set_planet_generation_weights(const json& planet_generation_weights_json);

    static void set_minimum_planets_per_generation(uint8_t minimum);

    static void set_maximum_planets_per_generation(uint8_t maximum);

    /** Generates and returns a vector of Planets representing a star system, respective to the 
     * passed game difficulty. */
    static std::vector<Planet> generate_planet_system();

private:
    
    // Members

    // Minimum number of planets that can be generated per system at the specified difficulty.
    static uint8_t s_minimum_planets_per_generation;

    // Maximum number of planets that can be generated per system at the specified difficulty.
    static uint8_t s_maximum_planets_per_generation;

    // Planet types that will be sampled from per each planet generation query.
    static WeightedDistribution<PLANET_TYPE, 12> s_planet_type_options;

    // Methods

    static Planet _generate_icy_dwarf();
    static Planet _generate_rocky_dwarf();
    static Planet _generate_metallic_dwarf();
    static Planet _generate_arctic_world();
    static Planet _generate_desert_world();
    static Planet _generate_terrestrial_planet();
    static Planet _generate_rocky_planet();
    static Planet _generate_lava_world();
    static Planet _generate_ice_giant();
    static Planet _generate_super_earth();
    static Planet _generate_gas_giant();
    static Planet _generate_dense_gas_giant();
};


