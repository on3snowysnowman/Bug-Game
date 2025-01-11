/**
 * @file Planet.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single class declaration & implementation.
 * @version 0.1
 * @date 01-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <cstdint>
#include <string>


enum PLANET_TYPE : uint8_t
{
    ICY_DWARF,
    ROCKY_DWARF,
    METALLIC_DWARF,
    ARCTIC_WORLD,
    DESERT_WORLD,
    TERRESTRIAL_PLANET,
    ROCKY_PLANET,
    LAVA_WORLD,
    ICE_GIANT,
    SUPER_EARTH,
    GAS_GIANT,
    DENSE_GAS_GIANT
};


/** Pure storage struct. Contains data for a single Planet in the planetary system. */
struct Planet
{
    PLANET_TYPE planet_type;

    // Size of the planet. The number of districts it supports.
    uint8_t size;

    // Unitless distance that represents the radius from the planet to the star.
    uint8_t distance_from_star;

    // Readable version of the enum planet_type.
    std::string planet_type_readable;

    // Name of the planet
    std::string name;
};
