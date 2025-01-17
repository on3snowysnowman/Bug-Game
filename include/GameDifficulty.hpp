/**
 * @file Difficulty.hpp
 * @author Joel Height (On3SnowySnowman@gmail.com)
 * @brief Single enum declaration & implementation.
 * @version 0.1
 * @date 01-10-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <cstdint>
#include <array>


/** Difficulty of the player's game experience. Changes many aspects of the game, including
 * planet and system generation along with bug strength and numbers. */
enum GAME_DIFFICULTY : uint8_t
{
    ROUTINE_OPERATION,
    LOW_RESISTANCE,
    STANDARD_PROTOCOL,
    UNYIELDING_FRONTLINES,
    THEN_THERE_WERE_BUGS
};

/** Names of each of the game difficulty types. The index of the array corresponds to the same 
 * difficulty type represented by the enum GAME_DIFFICULTY. */
constexpr std::array<const char*, 5> GAME_DIFFICULTY_NAMES 
    {"Routine Operation", "Low Resistance", "Standard Protocol", "Unyielding Frontlines",
    "Then, There Were Bugs"};

