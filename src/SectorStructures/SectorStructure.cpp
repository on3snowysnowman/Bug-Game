/**
 * @file SectorStructure.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 05-18-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SectorStructure.hpp"


// Constructors / Deconstructor

SectorStructure::SectorStructure() 
{
    m_struct_type = ORE_MINE;
    m_sector = nullptr;
}

SectorStructure::SectorStructure(Sector* sector, STRUCTURE_TYPE struct_type)
{
    m_sector = sector;
    m_struct_type = struct_type;
}


// Public

void SectorStructure::tick() {}


// Private


