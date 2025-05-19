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

#include "SectorStructure.hpp"


class OreMine : public SectorStructure
{

public:

    OreMine();

    OreMine(Sector* sector);

    void tick() final;

private:

    uint16_t m_ore_gen_per_tick = 2;

};
