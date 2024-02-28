/**
 * @file computerplayer.cpp
 * @brief Implementation file for the ComputerPlayer class.
 *
 * This file contains the implementation of the ComputerPlayer class.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "computerplayer.h"
#include "aifactory.h"

namespace tictactoe{

    /**
     * @brief Constructor for the ComputerPlayer class.
     *
     * @param symbol The symbol associated with the player.
     * @param ai The AI strategy used by the computer player.
     */
    ComputerPlayer::ComputerPlayer(Symbol symbol, std::unique_ptr<GameAI> ai)
        : Player(symbol, std::move(ai)) {}

    /**
     * @brief Makes a move on the board using the computer player's AI.
     *
     * @param point The position to make the move.
     * @param board The game board.
     * @return true if the move was successful, false otherwise.
     */
    bool ComputerPlayer::makeMove(const QPoint& point, Board& board){
        if (ai){
            QPoint move = ai->makeMove(board, symbol);
            curPos = move;
            return board.makeMove(move, getSymbol());
        }
        // No AI available to make a move, handle error
        Logger::getInstance().logError("Error: Invalid AI pointer: failed to make a move.", LOG_LOCATION);
        return false;
    }

    /**
     * @brief Changes the AI type of the computer player.
     *
     * @param aitype The new AI type.
     * @return True if the AI was changed successfully, false otherwise.
     */
    bool ComputerPlayer::changeAI(AIType aitype){
        // Delete the existing AI object
        ai.reset();

        // Create a new AI object based on the new AI type
        ai = AIFactory::createAI(aitype);
        if (!ai){
            // Failed to create AI, handle error
            Logger::getInstance().logError("AI Creation failed", LOG_LOCATION);
            return false;
        }
        return true; // AI changed successfully
    }

} // namespace tictactoe
