/**
 * @file Simulator.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single class implementation
 * @version 0.1
 * @date 01-11-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include  <iostream>

#include <EventHandler.hpp>
#include <MenuManager.hpp>

#include "Simulator.hpp"
#include "JsonHandler.hpp"
#include "PlanetSystemGenerator.hpp"
#include "NameGenerators.hpp"


// Constructors / Deconstructor

Simulator::Simulator() : FrostEngine() 
{
    _init();

    m_s_map_view_menu = SectorMapViewMenu(&m_coh, &m_sprite_handler);

    MenuManager::activate_menu(&m_s_map_view_menu);
}


// Public

void Simulator::set_difficulty(GAME_DIFFICULTY difficulty)
{
    m_current_game_difficulty = difficulty;
    _load_difficulty_config();
}

GAME_DIFFICULTY Simulator::get_difficulty() const { return m_current_game_difficulty; }


// Private

void Simulator::_init() 
{
    // m_sprite_handler.set_sprite_scale_factor(2);

    EventHandler::register_event<void, GAME_DIFFICULTY>("SET_DIFFICULTY", 
        std::function<void(GAME_DIFFICULTY)>([this](GAME_DIFFICULTY difficulty)
        { this->set_difficulty(difficulty); }));
    
    EventHandler::register_event<GAME_DIFFICULTY>("GET_DIFFICULTY", 
        std::function<GAME_DIFFICULTY()>([this]()
        { return this->get_difficulty(); }));

    set_difficulty(THEN_THERE_WERE_BUGS);
    NameGenerators::init();
}

void Simulator::_load_difficulty_config() 
{
    const json difficulty_config_json = 
        JsonHandler::get("data/difficulty_config.json").at(m_current_game_difficulty);

    m_current_game_difficulty_name = difficulty_config_json.at("Name");

    PlanetSystemGenerator::set_planet_generation_weights(
        difficulty_config_json.at("Planet Generation Weights"));

    PlanetSystemGenerator::set_minimum_planets_per_generation(
        difficulty_config_json.at("Minimum Planets Per Generation"));

    PlanetSystemGenerator::set_maximum_planets_per_generation(
        difficulty_config_json.at("Maximum Planets Per Generation"));
}
