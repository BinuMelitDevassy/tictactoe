/**
 * @file MinimaxAI.h
 * @brief Header file for the MinimaxAI class.
 *
 * This file contains the declaration of the MinimaxAI class, which implements the Minimax algorithm for AI moves.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef MINIMAXAI_H
#define MINIMAXAI_H

#include "gameai.h"

namespace tictactoe{
    /**
     * @brief The MinimaxAI class represents an AI player that makes moves using the Minimax algorithm.
     */
    class MinimaxAI : public GameAI {
    public:
        /**
         * @brief Constructor for creating a MinimaxAI object.
         */
        MinimaxAI();

        /**
         * @brief Makes a move using the Minimax algorithm.
         */
        QPoint makeMove(const Board& board, Symbol symbol) const override;

    private:
        /**
         * @brief Performs the Minimax algorithm recursively.
         */
        int minimax(const Board& board, int depth, bool maximizingPlayer, Symbol symbol) const;

        /**
         * @brief Calculates the score of the board for a given player.
         */
        int score(const Board& board, Symbol symbol) const;
    };

} // namespace tictactoe

#endif // MINIMAXAI_H
