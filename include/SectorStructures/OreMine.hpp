/**
 * @file OreMine.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 05-18-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Sector.hpp"
#include "SectorStructure.hpp"


class OreMine
{

public:

    OreMine();

    OreMine(Sector* sector);

    static void tick_thunk(void* obj);

    void tick();

private:

    uint16_t m_ore_gen_per_tick = 2;

    Sector* m_sector;
};
