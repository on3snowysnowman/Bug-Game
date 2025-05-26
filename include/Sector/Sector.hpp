/**
 * @file Sector.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Declaration of the Sector struct, which represents a sector and its 
 *        associated information.
 * @version 0.1
 * @date 04-29-25
 *
 * @copyright Copyright (c) 2024
 *
 */

 #pragma once

 #include <cstdint>
 #include <array>
 #include <vector>

 #include <Sprite.hpp>


enum SECTOR_TRAITS : uint8_t
{
   ORE_VEINS
};
 
constexpr uint16_t SECTOR_SPRITE_WIDTH = 88;
constexpr uint16_t ODD_SECTOR_SPRITE_WIDTH_OFFSET = 44;
constexpr uint16_t SECTOR_SPRITE_HEIGHT = 92;
constexpr uint16_t SECTOR_SPRITE_HEIGHT_OFFSET = 71;

/**
 * @brief Represents a map Sector with resources, power, defense, and traits.
 */
 struct Sector
 {    
   static constexpr uint32_t ORE_STORAGE_LIMIT = 2000;
   static constexpr uint32_t OIL_STORAGE_LIMIT = 5000;
   static constexpr uint32_t CRYSTAL_STORAGE_LIMIT = 400;
   static constexpr uint32_t METAL_STORAGE_LIMIT = 1000;
   static constexpr uint32_t ALLOY_STORAGE_LIMIT = 500;

    // Represents the defensive capability of this Sector. This value is used to 
    // determine the sector's resistance to attacks.
    uint8_t defense_level {};

    // Total power stored in this sector from batteries.
    uint32_t power_stored {}; 

    // Total power being supplied to this sector through the grid.
    uint32_t power_supplied {};

    /**    
    * Array representing the quantities of various resources in the Sector.
    * Resource indices:
    *   0 - Ore
    *   1 - Oil
    *   2 - Crystal
    *   3 - Metal
    *   4 - Alloy
    */
   std::array<uint32_t, 5> resources {0, 0, 0, 0, 0};

    // Trait names that are affecting this Sector.
    std::vector<SECTOR_TRAITS> traits;
 };
