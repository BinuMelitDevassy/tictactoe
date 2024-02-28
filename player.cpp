/**
 * @file player.cpp
 * @brief Implementation file for the Player class.
 *
 * This file contains the implementation of the Player class, which represents a player in the Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "player.h"

namespace tictactoe{

    /**
     * @brief Converts the player's symbol to a string representation.
     *
     * This function converts the Symbol enum value representing the player's symbol (X, O, or None) to a string.
     *
     * @return QString The string representation of the player's symbol.
     */
    QString Player::getSymbolString() const {
        int enumValue = static_cast<int>(symbol);
        QString symbolStr;
        switch (enumValue){
        case 0:
            symbolStr = NO_VAL;
            break;
        case 1:
            symbolStr = CROSS;
            break;
        case 2:
            symbolStr = CIRCLE;
            break;
        default:
            symbolStr = UNKNOWN;
        }
        return symbolStr;
    }

    /**
     * @brief Sets the level of the AI player.
     *
     * @param level_i The game level to set for the AI player.
     */
    void Player::setLevel(GameLevel level_i){
        if(ai){
            ai->setLevel(level_i);
        }
        else{
            Logger::getInstance().logError("Invalid ai", LOG_LOCATION);
        }

        }

} // namespace tictactoe
