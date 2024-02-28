/**
 * @file randomai.cpp
 * @brief Implementation file for the RandomAI class.
 *
 * This file contains the implementation of the RandomAI class, which represents an AI player that makes random moves in the Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "randomai.h"
#include <ctime>

namespace tictactoe{

    /**
     * @brief Constructs a new RandomAI object.
     *
     * This constructor initializes the RandomAI object.
     */
    RandomAI::RandomAI() : GameAI() {}

    /**
     * @brief Generates a random move for the AI player.
     *
     * This function generates a random move for the AI player by selecting a random empty cell on the board.
     *
     * @param board The current game board.
     * @param symbol The symbol of the AI player.
     * @return QPoint The randomly selected move represented by the row and column indices.
     */
    QPoint RandomAI::makeMove(const Board& board, Symbol symbol) const {
        // Seed the random number generator
        srand(static_cast<unsigned int>(time(nullptr)));

        // Get the board size
        int size = board.getSize();

        // Generate random row and column indices until an empty cell is found
        int row, col;
        do{
            row = rand() % size;
            col = rand() % size;
        } while (!board.isEmpty(QPoint(col, row))); // Note: QPoint uses (x, y) coordinates, so we swap col and row

        // Return the randomly selected move
        return QPoint(col, row); // Note: Swap col and row when creating the QPoint
    }

} // namespace tictactoe
