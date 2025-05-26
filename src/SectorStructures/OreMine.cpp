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

#include <Fr_Math.hpp>

// Constructors / Deconstructor

OreMine::OreMine() {}

OreMine::OreMine(Sector* sector) { m_sector = sector; }


// Public

void OreMine::tick_thunk(void* obj)
    { static_cast<OreMine*>(obj)->tick(); }

void OreMine::tick()
{
    std::array<uint32_t, 5>& sector_resources = m_sector->resources;

    sector_resources[0] += m_ore_gen_per_tick;

    // Clamp the sector's ore storage to its maximum if it exceeded it.
    sector_resources[0] = Frost::clamp_num_to_maximum<uint32_t>(
        sector_resources[0], Sector::ORE_STORAGE_LIMIT);
}


// Private


