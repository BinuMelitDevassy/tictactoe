/**
 * @file tictactoe.cpp
 * @brief Implementation file for the TicTacToe class.
 *
 * This file contains the implementation of the TicTacToe class, which represents the main game logic.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "tictactoe.h"
#include "computerplayer.h"
#include "humanplayer.h"
#include "aifactory.h"

namespace tictactoe{

    /**
     * @brief Constructs a new TicTacToe object.
     *
     * Initializes the game with default parameters and creates players.
     */
    TicTacToe::TicTacToe() : currentPlayer(nullptr),
        aitype_computer(AIType::Minimax),
        board(std::make_unique<Board>(DEFAULT_BOARD_SIZE)){
        createPlayers(Symbol::O);
    }

    /**
     * @brief Destroys the TicTacToe object.
     */
    TicTacToe::~TicTacToe(){}

    /**
     * @brief Starts a new game with the specified parameters.
     *
     * @param human_player The symbol chosen by the human player (X or O).
     * @param ai_type The type of AI used by the computer player.
     * @param board_size The size of the game board.
     */
    void TicTacToe::startNewGame(Symbol human_player, AIType ai_type, int board_size){

        if (!board){
            Logger::getInstance().logError("Invalid Board", LOG_LOCATION);
            return;
        }


        // Start a new game
        board->startNewGame(board_size);

        // Set the AI type for the computer player
        setAITypeComputer(ai_type);

        //set symbol
        Players[static_cast<int>(Player_Type::HUMAN)]->setSymbol(human_player);
        Players[static_cast<int>(Player_Type::COMPUTER)]->setSymbol( board->getOpponent(human_player));

        // Set the current player to the human player
        currentPlayer = Players[static_cast<int>(Player_Type::HUMAN)].get();

        if (!currentPlayer){
            Logger::getInstance().logError("Invalid Current Player", LOG_LOCATION);
        }
    }

    /**
     * @brief Attempts to make a move on the game board.
     *
     * @param pos The position to place the symbol.
     * @param type The type of player making the move (human or computer).
     * @return True if the move was successful, false otherwise.
     */
    bool TicTacToe::makeMove(const QPoint pos, Player_Type type){
        if (!currentPlayer){
            Logger::getInstance().logError("Invalid Current Player", LOG_LOCATION);
            return false;
        }
        currentPlayer = Players[static_cast<int>(type)].get();
        return currentPlayer->makeMove(pos, *board);
    }

    /**
     * @brief Checks for a winner on the game board.
     *
     * @return The type of player who won (human, computer, or unknown if no winner).
     */
    Player_Type TicTacToe::checkForWinner() const{

        if (!board){
            Logger::getInstance().logError("Invalid Board", LOG_LOCATION);
            return Player_Type::UNKNOWN;
        }

        Symbol symbol = board->checkForWinner();
        if (symbol == Symbol::None){
            return Player_Type::UNKNOWN;
        }
        else if (Players[static_cast<int>(Player_Type::HUMAN)]->getSymbol() == symbol){
            return Player_Type::HUMAN;
        }
        else if (Players[static_cast<int>(Player_Type::COMPUTER)]->getSymbol() == symbol){
            return Player_Type::COMPUTER;
        }
        else{
            return Player_Type::UNKNOWN;
        }
    }

    /**
     * @brief Gets the symbol of the current player.
     *
     * @return The symbol of the current player.
     */
    QString TicTacToe::getCurrentPlayerSymbol() const{
        if (!currentPlayer){
            Logger::getInstance().logError("Invalid Current Player", LOG_LOCATION);
            return QString("");
        }
        return currentPlayer->getSymbolString();
    }

    /**
     * @brief Gets the last move made by the computer player.
     *
     * @return The coordinates of the last move made by the computer player.
     */
    QPoint TicTacToe::getCurrentPosComputer() const{
        if (!Players[static_cast<int>(Player_Type::COMPUTER)]){
            // Handle error: Computer player not initialized
            Logger::getInstance().logError("Invalid Computer Player", LOG_LOCATION);
            return QPoint();
        }
        return Players[static_cast<int>(Player_Type::COMPUTER)]->getCurPos();
    }

    /**
     * @brief Checks if the game board is full.
     *
     * @return True if the game board is full, false otherwise.
     */
    bool TicTacToe::isBoardFull() const{
        if (!board){
            Logger::getInstance().logError("Invalid Board", LOG_LOCATION);
            return false;
        }
        return board->isBoardFull();
    }

    /**
     * @brief Creates the players for the game.
     *
     * @param human_player The symbol chosen by the human player (X or O).
     */
    void TicTacToe::createPlayers(Symbol human_player){
        for (int player = 0; player < PLAYER_COUNT; player++){
            switch (player){
            case static_cast<int>(Player_Type::COMPUTER):{
                std::unique_ptr<GameAI> ai = AIFactory::createAI(aitype_computer);

                if (ai){
                    Players[player] = std::make_unique<ComputerPlayer>(board->getOpponent(human_player), std::move(ai));
                }
                else{
                    Logger::getInstance().logError("AI Creation failed", LOG_LOCATION);
                }
                break;
            }
            case static_cast<int>(Player_Type::HUMAN):
                Players[player] = std::make_unique<HumanPlayer>(human_player, nullptr);
                break;
            default:
                break;
            }
        }
    }

    /**
     * @brief Sets the game level for the computer player.
     *
     * @param level The game level to set.
     */
    void TicTacToe::setGameLevel(GameLevel level){
        if (!Players[static_cast<int>(Player_Type::COMPUTER)]){
            Logger::getInstance().logError("Invalid Player", LOG_LOCATION);
            return;
        }
        Players[static_cast<int>(Player_Type::COMPUTER)]->setLevel(level);
    }

    /**
     * @brief Sets the AI type for the computer player.
     *
     * @param aitype_i The AI type to set.
     */
    void TicTacToe::setAITypeComputer(AIType aitype_i){
        if (!Players[static_cast<int>(Player_Type::COMPUTER)]){
            Logger::getInstance().logError("Invalid Player", LOG_LOCATION);
            return;
        }
        if (aitype_computer != aitype_i){
            aitype_computer = aitype_i;
            Players[static_cast<int>(Player_Type::COMPUTER)]->changeAI(aitype_computer);
        }
    }

} // namespace tictactoe
