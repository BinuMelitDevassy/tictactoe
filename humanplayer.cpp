/**
 * @file HumanPlayer.cpp
 * @brief Implementation file for the HumanPlayer class.
 *
 * This file contains the implementation of the HumanPlayer class, which represents a human player in a Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "humanplayer.h"

namespace tictactoe{

    /**
     * @brief Constructs a HumanPlayer object.
     *
     * @param symbol The symbol associated with the player.
     * @param ai The AI strategy used by the player.
     */
    HumanPlayer::HumanPlayer(Symbol symbol, std::unique_ptr<GameAI> ai)
        : Player(symbol, std::move(ai)) {}


    /**
     * @brief Makes a move on the board.
     *
     * @param pos The position to make the move.
     * @param board The game board.
     * @return True if the move was successful, false otherwise.
     */
    bool HumanPlayer::makeMove(const QPoint& pos, Board& board){
        // Check if the position is valid
        if (pos.x() < 0 || pos.x() >= board.getSize() || pos.y() < 0 || pos.y() >= board.getSize()){
            return false; // Invalid move
        }

        // Set the current position
        curPos = pos;

        // Make the move on the board
        return board.makeMove(pos, symbol);
    }

} // namespace tictactoe
