/**
 * @file minimaxai.cpp
 * @brief Implementation file for the MinimaxAI class.
 *
 * This file contains the implementation of the MinimaxAI class, which represents an AI player using the Minimax algorithm for decision-making in Tic-Tac-Toe.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "minimaxai.h"

namespace tictactoe{

    /**
     * @brief Constructor for the MinimaxAI class.
     *
     * Initializes a MinimaxAI object.
     */
    MinimaxAI::MinimaxAI() : GameAI() {}

    /**
     * @brief Makes a move using the Minimax algorithm.
     *
     * This function determines the best move to make using the Minimax algorithm.
     *
     * @param board The current state of the game board.
     * @param symbol The symbol (X or O) representing the player making the move.
     * @return QPoint The coordinates of the best move to make.
     */
    QPoint MinimaxAI::makeMove(const Board& board, Symbol symbol) const{
        int bestScore = -std::numeric_limits<int>::max();
        QPoint bestMove;

        // Iterate over all empty positions on the board
        for (int row = 0; row < board.getSize(); row++){
            for (int col = 0; col < board.getSize(); col++){
                if (board.isEmpty(QPoint(col, row))){
                    // Create a copy of the board and make a move on the temporary board
                    Board tempBoard = board;
                    tempBoard.makeMove(QPoint(col, row), symbol);
                    int score_calc = minimax(tempBoard, static_cast<int>(level), false, symbol);
                    if (score_calc > bestScore){
                        bestScore = score_calc;
                        bestMove = { col,row };
                    }
                }
            }
        }

        return bestMove;
    }


    /**
     * @brief Implementation of the Minimax algorithm for finding the optimal move in Tic Tac Toe.
     *
     * This function recursively evaluates all possible moves on the board and selects the best move using the Minimax algorithm.
     * Reference: https://www.geeksforgeeks.org/finding-optimal-move-in-tic-tac-toe-using-minimax-algorithm-in-game-theory/
     *
     * @param board The current state of the game board.
     * @param depth The depth of recursion (current depth of the search tree).
     * @param isMaximizing Indicates whether it's the maximizing player's turn or not.
     * @param symbol The symbol (X or O) for which the move is being evaluated.
     * @return The optimal score for the current move.
     */
	int MinimaxAI::minimax(const Board& board, int depth, bool isMaximizing, Symbol symbol) const
    {
        Symbol winner = board.checkForWinner();
        if (Symbol::None != winner){
            return score(board, symbol);
        }

        if (board.isBoardFull()){
            return 0; // Tie game
        }

        if ( 0 == depth){
            return 0;
        }

        int bestScore = isMaximizing ? -std::numeric_limits<int>::max() : std::numeric_limits<int>::max();
        for (int row = 0; row < board.getSize(); row++) {
            for (int col = 0; col < board.getSize(); col++){
                if (board.isEmpty(QPoint(col, row))){
                    // Create a copy of the board and make a move on the temporary board
                    Board tempBoard = board;
                    tempBoard.makeMove(QPoint(col, row), isMaximizing ? symbol : board.getOpponent(symbol));
                    int score_calc = minimax(tempBoard, depth - 1, !isMaximizing, symbol);
                    if (isMaximizing){
                        bestScore = std::max(bestScore, score_calc);
                    }
                    else{
                        bestScore = std::min(bestScore, score_calc);
                    }
                }
            }
        }

        return bestScore;
    }

    /**
     * @brief Computes the score for the given board state and player symbol.
     *
     * This function evaluates the score of the current board state for the specified player symbol.
     * The score is computed based on the number of winning positions, potential winning positions, and blocked positions.
     *
     * @param board The current state of the game board.
     * @param symbol The symbol (X or O) for which the score is being evaluated.
     * @return The score for the current board state and player symbol.
     */
    int MinimaxAI::score(const Board& board, Symbol symbol) const
    {
        Symbol winner = board.checkForWinner();
        if (winner == symbol){
            return DEFAULT_MAX_SCORE; // Player wins
        }
        else if (board.getOpponent(symbol) == winner){
            return DEFAULT_MIN_SCORE; // Opponent wins
        }
        else{
            return 0; // Draw
        }
    }

} // namespace tictactoe
