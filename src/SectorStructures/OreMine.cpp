/**
 * @file OreMine.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 05-18-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "OreMine.hpp"


// Constructors / Deconstructor

OreMine::OreMine() : SectorStructure() {}

OreMine::OreMine(Sector* sector) : SectorStructure(sector, ORE_MINE) {}


// Public

void OreMine::tick()
{
    m_sector->resources[0] += m_ore_gen_per_tick;
}


// Private


