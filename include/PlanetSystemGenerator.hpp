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

#include "Planet.hpp"
#include "GameDifficulty.hpp"


/** Static class that generates procedural planet populated systems. */
class PlanetSystemGenerator
{

public:

    /** Generates and returns a vector of Planets representing a star system, respective to the 
     * passed game difficulty. */
    static std::vector<Planet> generate_planet_system(GameDifficulty game_difficulty);

private:

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


