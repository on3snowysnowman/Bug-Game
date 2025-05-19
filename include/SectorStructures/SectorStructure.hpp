/**
 * @file SectorStructure.hpp
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


enum STRUCTURE_TYPE
{
    ORE_MINE
};


class SectorStructure
{

public:

    SectorStructure();

    SectorStructure(Sector* sector, STRUCTURE_TYPE struct_type);

    /**
     * @brief Called once per game tick. Handles any 'update' functionality
     * for this structure.
     */
    virtual void tick();

protected:

    STRUCTURE_TYPE m_struct_type;

    // Sector this structure exists on.
    Sector* m_sector;

};
