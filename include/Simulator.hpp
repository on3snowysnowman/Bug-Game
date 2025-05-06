/**
 * @file Simulator.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single class declaration.
 * @version 0.1
 * @date 01-11-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <FrostEngine.hpp>

#include "GameDifficulty.hpp"
#include "MainMenu.hpp"
#include "SectorMapViewMenu.hpp"

class Simulator : public FrostEngine
{

public:

    Simulator();

    /**
     * Sets the difficulty of the simulation, handling the loading of difficulty configurations and
     * settings any values affected changing the difficulty.
     */
    void set_difficulty(GAME_DIFFICULTY difficulty);

    /** Returns the current difficulty. */
    GAME_DIFFICULTY get_difficulty() const;

private:

    // Methods

    // Called on class creation, initializes internal components and sets up the simulator.
    void _init();

    // Opens the difficulty config file and loads the
    void _load_difficulty_config();


    // Members

    // The difficulty the game is currently set at.
    GAME_DIFFICULTY m_current_game_difficulty;

    // The name of the current difficulty.
    std::string m_current_game_difficulty_name;

    MainMenu m_main_menu;

    SectorMapViewMenu m_s_map_view_menu;
};
