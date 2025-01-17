/**
 * @file MainMenu.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single class declaration.
 * @version 0.1
 * @date 01-11-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <vector>
#include <string>

#include <Menu.hpp>
#include <ConsoleOutputHandler.hpp>

#include "Planet.hpp"
#include "GameDifficulty.hpp"


class MainMenu : public Menu
{

public:

    MainMenu();

    MainMenu(ConsoleOutputHandler* coh);

    void start() final;
    void update() final;


private:

    // Members

    // Current game difficulty.
    GAME_DIFFICULTY m_current_difficulty;

    std::string m_output;

    ConsoleOutputHandler* m_coh;


    // Methods

    void _generate_planets();
};
