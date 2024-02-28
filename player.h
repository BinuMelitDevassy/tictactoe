/**
 * @file Player.h
 * @brief Header file for the Player class.
 *
 * This file contains the declaration of the Player class, which represents a player in the Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "commondef.h"
#include "board.h"
#include "gameai.h"

namespace tictactoe{

    /**
     * @brief The Player class represents a player in the Tic-Tac-Toe game.
     */
    class Player{
    public:
        /**
         * @brief Destructor for the Player class.
         */
        virtual ~Player() {} // Make the base class destructor virtual

        /**
         * @brief Makes a move on the board.
         */
        virtual bool makeMove(const QPoint& point, Board& board) = 0;

        /**
         * @brief Changes the AI type of the player.
         */
        virtual bool changeAI(AIType aitype) = 0;

        /**
         * @brief Gets the symbol of the player.
         */
        inline Symbol getSymbol() const { return symbol; }

        /**
         * @brief Gets the symbol of the player.
         */
        inline void setSymbol( Symbol symbol_i){ symbol = symbol_i; }

        /**
         * @brief Gets the symbol string of the player.
         */
        QString getSymbolString() const;

        /**
         * @brief Gets the current position of the player.
         */
        inline QPoint getCurPos() const { return curPos; }

        /**
         * @brief Sets the level of the AI player.
         */
        void setLevel(GameLevel level_i);

    protected:
        /**
         * @brief Constructor for the Player class.
         */
        Player(Symbol symbol, std::unique_ptr<GameAI> ai_i) : symbol(symbol), ai(std::move(ai_i)), curPos(0, 0) {}

    protected:
        std::unique_ptr<GameAI> ai; // Pointer to the AI for the player
        Symbol symbol; // Symbol of the player
        QPoint curPos; // Current position of the player
    };

} // namespace tictactoe

#endif // PLAYER_H
