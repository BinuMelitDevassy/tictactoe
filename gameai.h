/**
 * @file gameai.h
 * @brief Header file for the GameAI class.
 *
 * This file contains the declaration of the GameAI class, which represents the AI logic for making moves in the Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef GAMEAI_H
#define GAMEAI_H

#include "board.h"
#include "commondef.h"

namespace tictactoe{
    /**
     * @brief The GameAI class represents the AI logic for making moves in the Tic-Tac-Toe game.
     */
    class GameAI{
    public:
        /**
         * @brief Constructor for the GameAI class.
         */
        GameAI();

        /**
         * @brief Destructor for the GameAI class.
         */
        virtual ~GameAI() = default;

        /**
         * @brief Makes a move on the board.
         */
        virtual QPoint makeMove(const Board& board, Symbol symbol) const = 0;

        /**
         * @brief Sets the level of the game AI.
         */
        inline void setLevel(GameLevel level_i) { level = level_i;};

    protected:
        GameLevel level; /**< The level of the game AI. */
    };

} // namespace tictactoe

#endif // GAMEAI_H
