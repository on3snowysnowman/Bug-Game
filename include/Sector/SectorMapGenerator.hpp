/**
 * @file SectorMapGenerator.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 04-30-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <vector>

#include <GridNodeDistributor.hpp>


#include "Sector.hpp"


/**
 * @brief Generates a random Sector Map.
 * 
 */
class SectorMapGenerator
{

public:

    std::vector<Sector*> generate_sector_map(uint16_t sector_size);

private:

    // Members 

    uint16_t m_active_sector_size;

    uint16_t m_chunk_size = 3;

    /**
     * @brief The sector map that is currently being 'worked on' during 
     * generation.
     * 
     * If there is no generation occuring, this pointer is a nullptr.
     */
    std::vector<Sector*>* m_active_sector_map;

    GridNodeDistributor m_node_distr;


    // Methods

    void _place_ore_veins();

    /** Generates a randomized sector. */
    Sector* _create_sector();

};
