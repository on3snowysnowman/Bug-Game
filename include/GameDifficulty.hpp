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


/** Difficulty of the player's game experience. Changes many aspects of the game, including
 * planet and system generation and bug strength and numbers. */
enum GameDifficulty : uint8_t
{
    ROUTINE_OPERATION,
    LOW_RESISTANCE,
    STANDARD_PROTOCOL,
    UNYIELDING_FRONTLINES,
    THEN_THERE_WERE_BUGS
};
