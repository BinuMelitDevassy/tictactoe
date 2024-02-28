/**
 * @file common.h
 * @brief Header file for common definitions and constants.
 *
 * This file contains common definitions and constants used throughout the Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QPoint>
#include <QDebug>
#include "logger.h"

namespace tictactoe {
    // consts
    const int DEFAULT_BOARD_SIZE = 3;
    const int DEFAULT_MAX_SCORE = 10;
    const int DEFAULT_MIN_SCORE = -10;
    const int PLAYER_COUNT = 2;
    const int LAYOUT_WIDTH  = 500;
    const int LAYOUT_HEIGHT  = 500;

    const QString CROSS = "X";
    const QString CIRCLE = "O";
    const QString NO_VAL = "no val";
    const QString UNKNOWN = "Unknown";
    const QString TIE = "Tie Game!";
    const QString PLAYER_WON = "You Won!";
    const QString PLAYER_LOST = "You Lost!";
    const QString CLICK_START = "Click Start";
    const QString CLICK_CELL = "Click Cell";
    const QString INVALID_MOVE = "Invalid";
    const QString PC_CALC = "Thinking !";
    const QString ICON_PATH = "icon - 2.png";

    //enums
    enum class Symbol { None, X, O };
    enum class Player_Type : int{
        COMPUTER,
        HUMAN,
        UNKNOWN
    };
    enum class GameLevel : int{
        EASY = 0,
        MEDIUM = 1,
        HARD = 5,
        EXPERT = 10,
        MASTER = 20
    };

    enum class AIType { Random, Minimax };

} // namespace tictactoe

#endif // COMMON_H
