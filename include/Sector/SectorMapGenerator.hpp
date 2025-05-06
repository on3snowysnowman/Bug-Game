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

#include <Array2D.hpp>
#include <Fr_Random.hpp>
#include <SpriteHandler.hpp>

#include "Sector.hpp"


/**
 * @brief Generates a random Sector Map.
 * 
 */
class SectorMapGenerator
{

public:

    SectorMapGenerator() {}
    
    template<uint16_t N>
    Array2D<Sector*, N> generate_sector_map()
    {
        Array2D<Sector*, N> sector_grid;

        // Create Sectors.
        for(uint16_t i = 0; i < N; ++i)
        {
            for(uint16_t j = 0; j < N; ++j)
            {
                sector_grid.at(i, j) = create_sector(true);
            }
        }

        return sector_grid;
    }

private:

    /** Generates a randomized sector. */
    Sector* create_sector(bool even_sector)
    {
        Sector* s = new Sector;

        return s;
    }

};
