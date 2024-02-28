/**
 * @file HumanPlayer.h
 * @brief Header file for the HumanPlayer class.
 *
 * This file contains the declaration of the HumanPlayer class, which represents a human player
 * in the Tic Tac Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

namespace tictactoe{

    /**
     * @brief The HumanPlayer class represents a human player in the Tic Tac Toe game.
     */
    class HumanPlayer : public Player{
    public:
        /**
         * @brief Constructs a HumanPlayer object with the specified symbol and AI.
         */
        HumanPlayer(Symbol symbol, std::unique_ptr<GameAI> ai);

        /**
         * @brief Makes a move on the board at the specified position.
         */
        bool makeMove(const QPoint& pos, Board& board) override;

        /**
         * @brief Changes the AI type associated with the human player.
         */
        bool changeAI(AIType aitype) override { return true; }; // Implement in future
    };

} // namespace tictactoe

#endif // HUMANPLAYER_H
