/**
 * @file TicTacToe.h
 * @brief Header file for the TicTacToe class.
 *
 * This file contains the declaration of the TicTacToe class, which represents the Tic Tac Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
*/

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QString>
#include <memory>
#include "board.h"
#include "player.h"

namespace tictactoe{
    /**
     * @brief The TicTacToe class represents the Tic Tac Toe game.
     */
    class TicTacToe {
    public:
        /**
         * @brief Default constructor for the TicTacToe class.
         */
        TicTacToe();

        /**
         * @brief Destructor for the TicTacToe class.
         */
        ~TicTacToe();

        /**
         * @brief Starts a new game of Tic Tac Toe.
         */
        void startNewGame(Symbol human_player, AIType ai_type, int board_size = DEFAULT_BOARD_SIZE);

        /**
         * @brief Makes a move in the game.
         */
        bool makeMove(const QPoint pos, Player_Type type);

        /**
         * @brief Checks if there is a winner in the game.
         */
        Player_Type checkForWinner() const;

        /**
         * @brief Gets the symbol of the current player.
         */
        QString getCurrentPlayerSymbol() const;

        /**
         * @brief Gets the current position of the computer player.
         */
        QPoint getCurrentPosComputer() const;

        /**
         * @brief Checks if the game board is full.
         */
        bool isBoardFull() const;

        /**
         * @brief Sets the game level.
         */
        void setGameLevel(GameLevel level);

        /**
         * @brief Sets the AI type for the computer player.
         */
        void setAITypeComputer(AIType aitype_i);

    private:
        /**
         * @brief Creates the players for the game.
         */
        void createPlayers(Symbol human_player);

    private:
        std::unique_ptr<Board> board; ///< Pointer to the game board.
        Player* currentPlayer; ///< Pointer to the current player.
        std::unique_ptr<Player> Players[PLAYER_COUNT]; ///< Array of players.
        AIType aitype_computer; ///< The AI type for the computer player.
    };
}

#endif
