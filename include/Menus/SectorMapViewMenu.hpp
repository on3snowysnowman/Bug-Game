/**
 * @file SectorMapViewMenu.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 05-04-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include <Menu.hpp>
#include <Sprite.hpp>
#include <SpriteHandler.hpp>
#include <ConsoleOutputHandler.hpp>
#include <Array2D.hpp>

#include "Sector.hpp"
#include "SectorMapGenerator.hpp"

class SectorMapViewMenu : public Menu
{

public:

    SectorMapViewMenu();

    SectorMapViewMenu(ConsoleOutputHandler* coh, 
        SpriteHandler* sprite_handler);

    void start() final;

    void update() final;

private:

    struct RenderingObject
    {
        rendering_id ren_ID;
        const char* object_ID;
    };

    // Members

    static constexpr uint16_t s_SECTOR_MAP_SIZE = 6;

    static constexpr uint16_t s_SECTOR_MAP_START_X = 10;

    static constexpr uint16_t s_SECTOR_MAP_START_Y = 10;

    ConsoleOutputHandler* m_coh;
    SpriteHandler* m_sprite_handler;

    rendering_id m_cursor_ren_ID;

    std::pair<uint16_t, uint16_t> m_cursor_pos;

    std::string m_viewable_sector_position;

    Sprite m_light_gray_sector_sprite;
    Sprite m_dark_gray_sector_sprite;
    Sprite m_ore_sprite;
    Sprite m_cursor_sprite;

    std::vector<Sector*> m_sector_map;

    // Map of sprites that are being rendered on each sector tile.
    std::vector<std::vector<RenderingObject>> m_rendering_tracker_map;

    SectorMapGenerator m_map_generator;


    // Methods

    void _init_sector_map_sprites();

    void _init_sector_trait_sprite(uint16_t sector_col, 
        uint16_t sector_row);

    void _update_cursor_information();

    void _handle_input();

    void _generate_sector_map();

    void _clear_rendering_objects();
};

