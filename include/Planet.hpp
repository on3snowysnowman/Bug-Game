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
#include <array>


/** 
 * Types of the generateble planets. Use the 'PLANET_TYPE_NAMES' array to lookup the readable 
 * version of the type, using the enum value as the index. */
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

// Number of planet types. 
constexpr uint8_t NUM_PLANET_TYPES = 12;

/** Names of each of the planet types. The index of the array corresponds to the same planet type 
 * represented by the enum PLANET_TYPE. */
constexpr std::array<const char*, NUM_PLANET_TYPES> PLANET_TYPE_NAMES
    {"Icy Dwarf", "Rocky Dwarf", "Metallic Dwarf", "Arctic World", "Desert World", 
    "Terrestrial Planet", "Rocky Planet", "Lava World", "Ice Giant", "Super Earth",
    "Gas Giant", "Dense Gas Giant"};

/** Pure storage struct. Contains data for a single Planet in the planetary system. */
struct Planet
{
    PLANET_TYPE planet_type;

    // Size of the planet. The number of districts it supports.
    uint8_t size;

    // Unitless distance that represents the radius from the planet to the star.
    uint8_t distance_from_star;

    // Name of the planet
    std::string name;
};
