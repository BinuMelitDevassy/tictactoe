/**
 * @file RandomAI.h
 * @brief Header file for the RandomAI class.
 *
 * This file contains the declaration of the RandomAI class, which represents an AI player that makes random moves.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef RANDOMAI_H
#define RANDOMAI_H

#include "gameai.h"

namespace tictactoe{

    /**
     * @brief The RandomAI class represents an AI player that makes random moves.
     */
    class RandomAI : public GameAI{
    public:
        /**
         * @brief Constructor for the RandomAI class.
         */
        RandomAI();

        /**
         * @brief Makes a move on the board.
         */
        QPoint makeMove(const Board& board, Symbol symbol) const override;
    };

} // namespace tictactoe

#endif // RANDOMAI_H
