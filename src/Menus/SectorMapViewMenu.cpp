/**
 * @file SectorMapViewMenu.cpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 05-04-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "SectorMapViewMenu.hpp"

#include <iostream>

#include <InputHandler.hpp>

#include "SectorMapGenerator.hpp"


// Constructors / Deconstructor

SectorMapViewMenu::SectorMapViewMenu() : Menu("SECTOR_MAP_VIEW")
{
    m_coh = nullptr;
    m_sprite_handler = nullptr;
}

SectorMapViewMenu::SectorMapViewMenu(ConsoleOutputHandler* coh, 
    SpriteHandler* sprite_handler) : Menu("SECTOR_MAP_VIEW")
{
    m_coh = coh;
    m_sprite_handler = sprite_handler;

    m_light_gray_sector_sprite = m_sprite_handler->create_sprite(
        "assets/LightGraySector.png", 0, 0, SECTOR_SPRITE_WIDTH, 
        SECTOR_SPRITE_HEIGHT);

    m_dark_gray_sector_sprite = m_sprite_handler->create_sprite(
        "assets/DarkGraySector.png", 0, 0, SECTOR_SPRITE_WIDTH,
        SECTOR_SPRITE_HEIGHT);

    m_ore_sprite = m_sprite_handler->create_sprite("assets/Ore.png",
        0, 0, 16, 16);

    m_cursor_sprite = m_sprite_handler->create_sprite("assets/SectorCursor2.png", 
        0, 0, 88, 92);

    m_sector_map = m_map_generator.generate_sector_map(s_SECTOR_MAP_SIZE);
    m_rendering_tracker_map.resize(s_SECTOR_MAP_SIZE * s_SECTOR_MAP_SIZE);
}

// Public

void SectorMapViewMenu::start() 
{
    _init_sector_map_sprites();

    m_cursor_ren_ID = m_sprite_handler->render_sprite(m_cursor_sprite, 0, 0, 0, 
        0, 1);

    _update_cursor_information();
}

void SectorMapViewMenu::update() 
{
    _handle_input();

    m_coh->set_anchor(60);

    m_coh->add_str("Sector: ");
    m_coh->add_str(m_viewable_sector_position);

    // m_coh->add_new_line(2);
}


// Private

void SectorMapViewMenu::_init_sector_map_sprites()
{
    // Render even rows and even columns.
    for(uint16_t row = 0; row < s_SECTOR_MAP_SIZE; row += 2)
    {
        for(uint16_t col = 0; col < s_SECTOR_MAP_SIZE; col += 2)
        {
            // Render the sector at this coordinate and obtain its rendering 
            // ID.
            rendering_id ren_id = m_sprite_handler->render_sprite(
                m_light_gray_sector_sprite, 
                s_SECTOR_MAP_START_X + (SECTOR_SPRITE_WIDTH * col), 
                s_SECTOR_MAP_START_Y + (SECTOR_SPRITE_HEIGHT_OFFSET * row));
            
            m_rendering_tracker_map.at(
                (row * s_SECTOR_MAP_SIZE) + col).push_back(
                RenderingObject {ren_id, "SECTOR"});

            _init_sector_trait_sprite(col, row);
        }
    }

    // Render even rows and odd columns
    for(uint16_t row = 0; row < s_SECTOR_MAP_SIZE; row += 2)
    {
        for(uint16_t col = 1; col < s_SECTOR_MAP_SIZE; col += 2)
        {
            // Render the sector at this coordinate and obtain its rendering 
            // ID.
            rendering_id ren_id = m_sprite_handler->render_sprite(
                m_dark_gray_sector_sprite, 
                s_SECTOR_MAP_START_X + (SECTOR_SPRITE_WIDTH * col), 
                s_SECTOR_MAP_START_Y + (SECTOR_SPRITE_HEIGHT_OFFSET * row));
            
            m_rendering_tracker_map.at(
                (row * s_SECTOR_MAP_SIZE) + col).push_back(
                RenderingObject {ren_id, "SECTOR"});

            _init_sector_trait_sprite(col, row);
        }
    }

    // Render odd rows and even columns.
    for(uint16_t row = 1; row < s_SECTOR_MAP_SIZE; row+=2)
    {
        for(uint16_t col = 0; col < s_SECTOR_MAP_SIZE; col+=2)
        {
            // Render the sector at this coordinate and obtain its rendering 
            // ID.
            rendering_id ren_id = m_sprite_handler->render_sprite(
                m_light_gray_sector_sprite, 
                s_SECTOR_MAP_START_X + ODD_SECTOR_SPRITE_WIDTH_OFFSET +
                (SECTOR_SPRITE_WIDTH * col), 
                s_SECTOR_MAP_START_Y + (SECTOR_SPRITE_HEIGHT_OFFSET * row));
            
            m_rendering_tracker_map.at(
                (row * s_SECTOR_MAP_SIZE) + col).push_back(
                RenderingObject {ren_id, "SECTOR"});

            _init_sector_trait_sprite(col, row);
        }
    }

    // Render odd rows and odd columns.
    for(uint16_t row = 1; row < s_SECTOR_MAP_SIZE; row+=2)
    {
        for(uint16_t col = 1; col < s_SECTOR_MAP_SIZE; col+=2)
        {
            // Render the sector at this coordinate and obtain its rendering 
            // ID.
            rendering_id ren_id = m_sprite_handler->render_sprite(
                m_dark_gray_sector_sprite, 
                s_SECTOR_MAP_START_X + ODD_SECTOR_SPRITE_WIDTH_OFFSET +
                (SECTOR_SPRITE_WIDTH * col), 
                s_SECTOR_MAP_START_Y + (SECTOR_SPRITE_HEIGHT_OFFSET * row));
            
            m_rendering_tracker_map.at(
                (row * s_SECTOR_MAP_SIZE) + col).push_back(
                RenderingObject {ren_id, "SECTOR"});

            _init_sector_trait_sprite(col, row);
        }
    }
}

void SectorMapViewMenu::_init_sector_trait_sprite(uint16_t sector_col, 
    uint16_t sector_row)
{
    Sector* targ_sector = m_sector_map.at(
        (sector_row * s_SECTOR_MAP_SIZE) + sector_col);

    // No traits, no problem.
    if(targ_sector->traits.size() == 0) return;

    uint16_t trait_display_x = s_SECTOR_MAP_START_X +
        ((sector_row & 1) * ODD_SECTOR_SPRITE_WIDTH_OFFSET) + 
        (SECTOR_SPRITE_WIDTH / 2) - 8 + 
        (SECTOR_SPRITE_WIDTH * sector_col);

    uint16_t trait_display_y = s_SECTOR_MAP_START_Y +
        (SECTOR_SPRITE_HEIGHT / 2) - 8 + 
        (SECTOR_SPRITE_HEIGHT_OFFSET * sector_row);
        
    rendering_id trait_id;

    for(SECTOR_TRAITS trait : targ_sector->traits)
    {
        if(trait == ORE_VEINS)
        {
            trait_id = m_sprite_handler->render_sprite(m_ore_sprite,
                trait_display_x, trait_display_y, 0, 0, 1);
            m_rendering_tracker_map.at(
                (sector_row * s_SECTOR_MAP_SIZE) + sector_col).push_back(
                RenderingObject {trait_id, "ORE_VEINS"});
        }
    }
}

void SectorMapViewMenu::_update_cursor_information()
{
    uint16_t cursor_display_x_position = 
        s_SECTOR_MAP_START_X + 
        ((m_cursor_pos.second & 1) * ODD_SECTOR_SPRITE_WIDTH_OFFSET) +
        (SECTOR_SPRITE_WIDTH * m_cursor_pos.first);

    uint16_t cursor_display_y_position = 
        s_SECTOR_MAP_START_Y + 
        (SECTOR_SPRITE_HEIGHT_OFFSET * m_cursor_pos.second);

    m_viewable_sector_position = std::to_string(m_cursor_pos.first + 1) + ", " +
        std::to_string(m_cursor_pos.second + 1);

    m_sprite_handler->set_instance_position(m_cursor_ren_ID, 
        cursor_display_x_position, cursor_display_y_position);
}

void SectorMapViewMenu::_handle_input()
{
    for(const Key& key : InputHandler::get_pressed_and_available_keys())
    {
        switch(key)
        {
            case SDLK_UP:

                if(m_cursor_pos.second == 0) continue;

                m_cursor_pos.second -= 1;;
                InputHandler::delay_key(SDLK_UP, 215);

                _update_cursor_information();
                break;
            
            case SDLK_RIGHT: 

                if(m_cursor_pos.first >= s_SECTOR_MAP_SIZE - 1) continue;

                m_cursor_pos.first += 1;
                InputHandler::delay_key(SDLK_RIGHT, 215);

                _update_cursor_information();
                break;

            case SDLK_DOWN:

                if(m_cursor_pos.second >= s_SECTOR_MAP_SIZE - 1) continue;

                m_cursor_pos.second += 1;
                InputHandler::delay_key(SDLK_DOWN, 215);

                _update_cursor_information();
                break;

            case SDLK_LEFT:

                if(m_cursor_pos.first == 0) continue;

                m_cursor_pos.first -= 1;
                InputHandler::delay_key(SDLK_LEFT, 215);

                _update_cursor_information();
                break;

            case SDLK_RETURN:   

                _generate_sector_map();
                InputHandler::block_key_until_released(SDLK_RETURN);
                break;
        }
    }
}

void SectorMapViewMenu::_generate_sector_map()
{
    _clear_rendering_objects();
    m_sector_map = m_map_generator.generate_sector_map(s_SECTOR_MAP_SIZE);
    _init_sector_map_sprites();
}

void SectorMapViewMenu::_clear_rendering_objects()
{
    for(uint32_t i = 0; i < s_SECTOR_MAP_SIZE * s_SECTOR_MAP_SIZE; ++i)
    {
        // Iterate through each RenderingObject at this position.
        for(const RenderingObject& obj : m_rendering_tracker_map.at(i))
        {
            m_sprite_handler->unrender_sprite(obj.ren_ID);
        }

        m_rendering_tracker_map.at(i).clear();
    }
}
