/**
 * @file ComputerPlayer.h
 * @brief Header file for the ComputerPlayer class.
 *
 * This file contains the declaration of the ComputerPlayer class.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <memory>
#include "commondef.h"
#include "player.h"

namespace tictactoe{
    /**
    * @brief The ComputerPlayer class represents a computer player in the Tic-Tac-Toe game.
    */
    class ComputerPlayer : public Player{
    public:
        /**
         * @brief Constructor for ComputerPlayer class.
         */
        ComputerPlayer(Symbol symbol, std::unique_ptr<GameAI> ai);

        /**
         * @brief Makes a move on the board.
         */
        bool makeMove(const QPoint& point, Board& board) override;

        /**
         * @brief Changes the AI strategy.
         */
        bool changeAI(AIType aitype) override;
    };

} // namespace tictactoe

#endif // COMPUTERPLAYER_H
