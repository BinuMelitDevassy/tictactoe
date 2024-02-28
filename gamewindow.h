/**
 * @file gamewindow.h
 * @brief Header file for the GameWindow class.
 *
 * This file contains the declaration of the GameWindow class, which represents
 * the main window of the Tic Tac Toe game application.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include "tictactoe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

/**
 * @brief The GameWindow class represents the main window of the Tic Tac Toe game application.
 */
class GameWindow : public QMainWindow{
    Q_OBJECT

public:
    /**
     * @brief Constructs a GameWindow object.
     */
    explicit GameWindow(QWidget* parent = nullptr);

    /**
     * @brief Destroys the GameWindow object.
     */
    ~GameWindow();

private slots:
    /**
     * @brief Slot function called when a game button is clicked.
     */
    void onButtonClick();

    /**
     * @brief Slot function called when the start button is clicked.
     */
    void on_Start_button_clicked();

    /**
     * @brief Slot function called when the radio button for X is clicked.
     */
    void on_radioButton_clicked();

    /**
     * @brief Slot function called when the radio button for O is clicked.
     */
    void on_radioButton_2_clicked();

    /**
     * @brief Slot function called when the grid size value is changed.
     */
    void on_Grid_size_valueChanged(int arg1);

    /**
     * @brief Slot function called when the game level value is changed.
     */
    void on_Game_level_valueChanged(int arg1);

private:
    /**
     * @brief Creates the buttons for the game board.
     */
    void createButtons();

    /**
     * @brief Updates the user interface after a move is made.
     */
    void updateUI(int row, int col);

    /**
     * @brief Toggles the enable/disable state of the game board buttons.
     */
    void toggleBoard(bool enable, bool resetText);

    /**
     * @brief Displays the winner of the game.
     */
    void displayWinner(tictactoe::Player_Type winner);

    /**
     * @brief Initiates the computer's move.
     */
    void computerMove();

    /**
     * @brief Handles the end of the game.
     */
    bool handleGameEnd();

    /**
     * @brief Updates the text of a button after a move.
     */
    void updateButton(int row, int col);

    /**
     * @brief Restarts the game with the provided message.
     */
    void Restartgame(QString msg);

    /**
     * @brief Enables or disables the symbol selection.
     */
    void enableSelectSymbol(bool enable);

    /**
     * @brief Enables or disables the user interface elements.
     */
    void enableUI(bool enable);

    /**
     * @brief Set up symbol selection radio buttons.
     */
    void setupSymbolSelection();

private:
	Ui::GameWindow* ui; /**< The user interface object. */
	tictactoe::TicTacToe* game; /**< The Tic Tac Toe game object. */
	tictactoe::Symbol symbol; /**< The symbol selected by the player. */
	QGridLayout* buttonLayout; /**< The layout for the game buttons. */
	QButtonGroup* buttonGroup; /**< The button group for radio buttons. */
	int size; /**< The size of the game board. */
};

#endif // GAMEWINDOW_H
