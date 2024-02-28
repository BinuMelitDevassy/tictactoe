/**
 * @file Board.cpp
 * @brief Implementation file for the Board class.
 *
 * This file contains the implementation of the Board class which represents the game board.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#include "board.h"

namespace tictactoe{

    /**
     * @brief Constructor for the Board class.
     *
     * @param size The size of the board.
     */
    Board::Board(int size_i) : size(size_i){
        board.resize(size, std::vector<Symbol>(size, Symbol::None));
    }

    /**
     * @brief Starts a new game by resetting the board.
     *
     * @param size The size of the board.
     */
    void Board::startNewGame(int size_i){

        // if size changed
        if(size_i != size ){
            size = size_i;
            // Initialize the board
            //board.resize(size, std::vector<Symbol>(size, Symbol::None));

            // Resize the board vector
            board.resize(size);

            // Initialize each row with Symbol::None
            for (int row = 0; row < size; ++row) {
                board[row].resize(size, Symbol::None);
            }
        }
        // Reset the board
        for (int row = 0; row < size; row++){
            for (int col = 0; col < size; col++){
                board[row][col] = Symbol::None;
            }
        }
    }

    /**
     * @brief Attempts to make a move on the board.
     *
     * @param pos The position on the board to make the move.
     * @param symbol The symbol to place on the board.
     * @return true if the move was successful, false otherwise.
     */
    bool Board::makeMove(const QPoint& pos, Symbol symbol){
        int row = pos.y();
        int col = pos.x();
        // Make a move on the board
        if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != Symbol::None){
            Logger::getInstance().logError("Failed to make a move", LOG_LOCATION);
            return false; // Invalid move
        }

        board[row][col] = symbol;
        return true;  // Move successful
    }

    /**
     * @brief Checks if there is a winner on the board.
     *
     * @return The symbol of the winner if there is one, Symbol::None otherwise.
     */
    Symbol Board::checkForWinner() const{
        // Check Rows
        for (int row = 0; row < size; row++){
            if (checkSequence(board[row][0], row, 0, 0, 1) && board[row][0] != Symbol::None){
                return board[row][0]; // Winner in this row
            }
        }

        // Check Columns
        for (int col = 0; col < size; col++){
            if (checkSequence(board[0][col], 0, col, 1, 0) && board[0][col] != Symbol::None){
                return board[0][col]; // Winner in this column
            }
        }

        // Check Diagonal from top-left to bottom-right
        if (checkSequence(board[0][0], 0, 0, 1, 1) && board[0][0] != Symbol::None){
            return board[0][0]; // Top-left to bottom-right diagonal
        }

        // Check Diagonal from top-right to bottom-left
        if (checkSequence(board[0][size - 1], 0, size - 1, 1, -1) && board[0][size - 1] != Symbol::None){
            return board[0][size - 1]; // Top-right to bottom-left diagonal
        }

        // Check for a tie (already implemented)
        if (isBoardFull()){
            return Symbol::None; // Tie game
        }

        return Symbol::None; // No winner
    }

    /**
     * @brief Checks for a winning sequence on the board.
     *
     * @param symbol The symbol to check for.
     * @param startRow The starting row index.
     * @param startCol The starting column index.
     * @param dRow The row increment.
     * @param dCol The column increment.
     * @return true if a winning sequence is found, false otherwise.
     */
    bool Board::checkSequence(Symbol symbol, int startRow, int startCol, int dRow, int dCol) const{
        for (int i = 1; i < size; i++){
            int row = startRow + i * dRow;
            int col = startCol + i * dCol;
            if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != symbol){
                return false; // Sequence not the same
            }
        }
        return true; // Sequence is the same
    }

    /**
     * @brief Checks if the board is full.
     *
     * @return true if the board is full, false otherwise.
     */
    bool Board::isBoardFull() const{
        // Check if the board is full
        for (int row = 0; row < size; row++){
            for (int col = 0; col < size; col++){
                if ( Symbol::None == board[row][col]){
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * @brief Checks if a position on the board is empty.
     *
     * @param pos The position to check.
     * @return true if the position is empty, false otherwise.
     */
    bool Board::isEmpty(const QPoint& pos) const{
        int row = pos.y();
        int col = pos.x();
        // Check if the specified position is empty
        return row >= 0 && row < size && col >= 0 && col < size && Symbol::None == board[row][col];
    }

    /**
     * @brief Gets the opponent symbol.
     *
     * @param symbol The symbol of the current player.
     * @return The symbol of the opponent player.
	 */
	Symbol Board::getOpponent(Symbol symbol) const
	{
		// Return the opponent's symbol
		if (Symbol::X == symbol){
			return Symbol::O;
		}
		else if (Symbol::O == symbol){
			return Symbol::X;
		}
		else{
			return Symbol::None; // No opponent for None symbol
		}
	}

} // namespace tictactoe
