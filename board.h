/**
 * @file Board.h
 * @brief Header file for the Board class.
 *
 * This file contains the declaration of the Board class.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "commondef.h"

namespace tictactoe{
    /**
     * @brief The Board class represents a Playing Board in the Tic-Tac-Toe game.
    */
    class Board{
    public:
        /**
         * @brief Constructor for creating a board with a specified size.
         */
        explicit Board(int size_i = DEFAULT_BOARD_SIZE);

        /**
         * @brief Starts a new game by resetting the board.
         */
        void startNewGame(int size_i);

        /**
         * @brief Attempts to make a move on the board.
         */
        bool makeMove(const QPoint& pos, Symbol symbol);

        /**
         * @brief Checks if there is a winner on the board.
         */
        Symbol checkForWinner() const;

        /**
         * @brief Checks if the board is full.
         */
        bool isBoardFull() const;

        /**
         * @brief Gets the size of the board.
         */
        inline int getSize() const { return size; }

        /**
         * @brief Checks if a position on the board is empty.
         */
        bool isEmpty(const QPoint& pos) const;

        /**
         * @brief Gets the opponent symbol.
         */
        Symbol getOpponent(Symbol symbol) const;

    private:
        /**
         * @brief Checks for a winning sequence on the board.
         */
        bool checkSequence(Symbol symbol, int startRow, int startCol, int dRow, int dCol) const;

    private:
        int size; // Size of the board
        std::vector<std::vector<Symbol>> board; // 2D vector to represent the board
    };

} // namespace tictactoe

#endif // BOARD_H
