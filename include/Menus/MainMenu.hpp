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

    uint8_t m_current_font_index {};

    uint16_t m_focus {};

    std::string m_output;

    ConsoleOutputHandler* m_coh;

    const std::vector<std::string>* m_font_paths;


    // Methods

    void _generate_planets();
};
