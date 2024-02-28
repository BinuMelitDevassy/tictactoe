/**
 * @file gameai.cpp
 * @brief Implementation file for the GameAI class.
 *
 * This file contains the implementation of the GameAI class.
 * The GameAI class represents the artificial intelligence (AI) used in the Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "gameai.h"

namespace tictactoe {

	/**
	 * @brief Default constructor for the GameAI class.
	 *
	 * Initializes the AI level to the default level (EASY).
	 */
	GameAI::GameAI() : level(GameLevel::EASY) {}

} // namespace tictactoe
