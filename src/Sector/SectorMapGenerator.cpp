/**
 * @file SectorMapGenerator.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 05-16-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SectorMapGenerator.hpp"

#include <iostream>

// Constructors / Deconstructor


// Public

std::vector<Sector*> SectorMapGenerator::generate_sector_map(uint16_t sector_size)
{   
    if(sector_size % 3 != 0) return {};

    m_active_sector_size = sector_size;

    std::vector<Sector*> sector_map;
    sector_map.reserve(sector_size * sector_size);

    // Pointer to local stack allocated memory, this is handled at the end of 
    // the function where the pointer is reset to a nullptr after all sector 
    // map generation is finished.
    m_active_sector_map = &sector_map;

    for(uint32_t i = 0; i < sector_size * sector_size; ++i)
    {
        sector_map.push_back(_create_sector());
    }

    _place_ore_veins();

    // Reset the active sector map to nullptr, to not leave a dangling pointer
    // to soon-invalid local stack allocated memory.
    m_active_sector_map = nullptr;

    return sector_map;
}



// Private

void SectorMapGenerator::_place_ore_veins()
{
    for(const Point2D& point : m_node_distr.get_single_value_node_distribution(
        m_active_sector_size, m_active_sector_size, m_chunk_size, m_chunk_size, 1,
        25, 1))
    {
        m_active_sector_map->at((point.y * m_active_sector_size) + point.x)->
            traits.push_back(ORE_VEINS);
    }
}

Sector* SectorMapGenerator::_create_sector()
{
    Sector* sector = new Sector;

    return sector;
}



