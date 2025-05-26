/**
 * @file SectorStructureUpdateHandler.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 05-20-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <vector>
#include <functional>


class StructureTickHandler
{

public:

    StructureTickHandler() {}

    template<typename T> 
    void add_structure(T* structure)
    {
        // Add this funciton's tick function to the list.
        m_structure_tick_functions.push_back(
            [structure() { structure->tick(); }]);
    }

    void update_all_structures() 
    {
        // Iterate through all the tick functions and call them.
        for(const std::function<void()>& tick_function : 
            m_structure_tick_functions) tick_function();
    }


private:

    std::vector<std::function<void()>> m_structure_tick_functions;

};

