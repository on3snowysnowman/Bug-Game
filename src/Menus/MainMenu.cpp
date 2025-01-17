/**
 * @file MainMenu.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single class implementation
 * @version 0.1
 * @date 01-11-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <sstream>

#include "MainMenu.hpp"
#include "PlanetSystemGenerator.hpp"
#include "EventHandler.hpp"
#include "InputHandler.hpp"


// Constructors / Deconstructor

MainMenu::MainMenu() : Menu("MAIN") {}

MainMenu::MainMenu(ConsoleOutputHandler* coh) : Menu("MAIN")
{
    m_coh = coh;
}


// Public

void MainMenu::start() 
{
    m_current_difficulty = EventHandler::invoke_event<GAME_DIFFICULTY>("GET_DIFFICULTY");

    _generate_planets();
}

void MainMenu::update() 
{

    if(InputHandler::is_key_pressed_and_available(SDLK_RETURN))
    {
        _generate_planets();

        InputHandler::block_key_until_released(SDLK_RETURN);
    }

    else if(InputHandler::is_key_pressed_and_available(SDLK_RIGHT))
    {
        // Increase the difficulty if it is not already at the max difficulty.
        m_current_difficulty = static_cast<GAME_DIFFICULTY>(
            m_current_difficulty + (m_current_difficulty != GAME_DIFFICULTY_NAMES.size() - 1));

        _generate_planets();

        InputHandler::block_key_until_released(SDLK_RIGHT);
    }

    else if(InputHandler::is_key_pressed_and_available(SDLK_LEFT))
    {
        // Increase the difficulty if it is not already at the min difficulty.
        m_current_difficulty = static_cast<GAME_DIFFICULTY>(
            m_current_difficulty - (m_current_difficulty != 0));

        _generate_planets();

        InputHandler::block_key_until_released(SDLK_LEFT);
    }

    m_coh->add_str(m_output);
}


// Private

void MainMenu::_generate_planets() 
{
    std::stringstream output_stream;

    output_stream << "\n[";

    for(uint8_t i = 0; i < m_current_difficulty; ++i)
    {
        output_stream << '.';
    }

    output_stream << '*';

    for(uint8_t i = m_current_difficulty + 1; i < GAME_DIFFICULTY_NAMES.size(); ++i)
    {
        output_stream << '.';
    }

    output_stream << "]\nDifficulty: " << GAME_DIFFICULTY_NAMES.at(m_current_difficulty) << "\n\n";

    for(const Planet& planet : PlanetSystemGenerator::generate_planet_system())
    {
        output_stream << "Name: " << planet.name << "\nType: " << 
            PLANET_TYPE_NAMES.at(planet.planet_type) << "\nDistance from Star: " << 
            int(planet.distance_from_star) << "\nSize: " << int(planet.size) << "\n\n";
    }

    m_output = output_stream.str();
}
