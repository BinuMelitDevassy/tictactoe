/**
 * @file gamewindow.cpp
 * @brief Implementation file for the GameWindow class.
 *
 * This file contains the implementation of the GameWindow class, which represents the main game window
 * for the Tic-Tac-Toe game.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include <QButtonGroup>
#include <QtConcurrent/QtConcurrent>
#include "gamewindow.h"
#include "ui_gamewindow.h"

/**
* @brief Constructor for the GameWindow class.
*
* @param parent The parent widget.
*/
GameWindow::GameWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , game(new tictactoe::TicTacToe)
    , symbol(tictactoe::Symbol::O)
    , size(tictactoe::DEFAULT_BOARD_SIZE) {

    try {
        ui->setupUi(this);

        // Setting ICON
        //QIcon icon(tictactoe::ICON_PATH);
        //setWindowIcon(icon);

        // Setup symbol selection radio btns
        setupSymbolSelection();

        // Set up grid layout
        buttonLayout = ui->gridLayout;
        createButtons();
        ui->Grid_size->setValue(size);

        // Set board appearance
        toggleBoard(false, true);
        ui->Result_text->setText(tictactoe::CLICK_START);
    }
    catch (const std::exception& e) {
        // Log the exception message
        tictactoe::Logger::getInstance().logError(e.what(), LOG_LOCATION);
    }
}

/**
 * @brief Destructor for the GameWindow class.
 */
GameWindow::~GameWindow() {
	if (ui) {
		delete ui;
		ui = nullptr;
	}
	if (game) {
		delete game;
		game = nullptr;
	}

	// Set other pointers to null after deletion
	buttonLayout = nullptr;
	buttonGroup = nullptr;
}

/**
 * @brief Creates buttons for the game board.
 */
void GameWindow::createButtons() {
    try{
		// Remove all existing buttons
		QLayoutItem* item = nullptr;
		while ((item = buttonLayout->takeAt(0)) != nullptr) {
			if (item->widget()) {
				delete item->widget();
			}
			delete item;
            item = nullptr;
		}

		// Get the size of the buttonLayout
		QSize layoutSize = buttonLayout->geometry().size();

        // Calculate the button width and height based on the layout size
        int buttonWidth = tictactoe::LAYOUT_WIDTH / size;
        int buttonHeight = tictactoe::LAYOUT_HEIGHT / size;

		for (int row = 0; row < size; ++row) {
			for (int col = 0; col < size; ++col) {
				QPushButton* button = new QPushButton();
                // setting button name based on pos
				button->setObjectName(QString("button_%1_%2").arg(row).arg(col));
				button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
				button->setFixedSize(buttonWidth, buttonHeight);
                // all buttons are connected to same slot
				connect(button, &QPushButton::clicked, this, &GameWindow::onButtonClick);
				buttonLayout->addWidget(button, row, col);

                // setting font based on button size
				int fontSize = qMin(buttonWidth, buttonHeight) / size;
				QFont font = button->font();
				font.setPointSize(fontSize);
				button->setFont(font);
			}
		}
    }
    catch (const std::exception& e) {
		// Log the exception message
		tictactoe::Logger::getInstance().logError(e.what(), LOG_LOCATION);
	}
}

/**
 * @brief Slot for handling button clicks.
 */
void GameWindow::onButtonClick() {
    try{
		QPushButton* button = qobject_cast<QPushButton*>(sender());
		if (!button) return;

		QString name = button->objectName();

        // getting the sender buttons row and col values
		// hard coded based on the name give "button_%1_%2"
		int row = name.mid(7, 1).toInt();
		int col = name.mid(9, 1).toInt();
		updateUI(row, col);
    }
	catch (const std::exception& e) {
		// Log the exception message
		tictactoe::Logger::getInstance().logError(e.what(), LOG_LOCATION);
	}
}

/**
 * @brief Updates the UI after a move.
 *
 * @param row The row index of the move.
 * @param col The column index of the move.
 */
void GameWindow::updateUI(int row, int col) {
    try {
        // Player's Move
        if (!game->makeMove(QPoint(col, row), tictactoe::Player_Type::HUMAN)) {
            // Invalid move, handle error here if needed
            ui->Result_text->setText(tictactoe::INVALID_MOVE);
            return;
        }
        updateButton(row, col);

        // Check for the end of the game
        if (handleGameEnd()) {
            // Now user can change Grid Size and Symbol
            ui->Grid_size->setEnabled(true);
            enableSelectSymbol(true);
            return; // Game is over
        }

        // Computer's Move
        // disabling all buttons until computer finished thinking
        enableUI(false);
        // starting computer movement in another thread
        QtConcurrent::run([this]() {
            this->computerMove();
            });
    }
	catch (const std::exception& e) {
		// Log the exception message
		tictactoe::Logger::getInstance().logError(e.what(), LOG_LOCATION);
	}
}


// Update button text after a move
/**
 * @brief Update the text of the button at the specified row and column after a move.
 *
 * @param row The row index of the button.
 * @param col The column index of the button.
 */
void GameWindow::updateButton(int row, int col)
{
    // Get the button at the specified position
    QLayoutItem* item = buttonLayout->itemAtPosition(row, col);
    QPushButton* button = qobject_cast<QPushButton*>(item->widget());
    if (button) {
        // Set the text of the button to the current player's symbol
        button->setText(game->getCurrentPlayerSymbol());
    }
}

// Handle end of the game
/**
 * @brief Check if the game has ended and perform the necessary actions.
 *
 * @return True if the game has ended, false otherwise.
 */
bool GameWindow::handleGameEnd()
{
    tictactoe::Player_Type winner = game->checkForWinner();
    if (tictactoe::Player_Type::UNKNOWN != winner) {
        displayWinner(winner);
        toggleBoard(false, false);  // Disable board
        return true;
    }
    else if (game->isBoardFull()) {
        ui->Result_text->setText(tictactoe::TIE);
        toggleBoard(false, false);
        return true;
    }
    else {
        return false; // Game continues
    }
}

// Perform the computer's move
/**
 * @brief Perform the computer's move.
 */
void GameWindow::computerMove()
{
    // Make the computer's move
    game->makeMove(QPoint(-1, -1), tictactoe::Player_Type::COMPUTER);
    // Update the corresponding button
    updateButton(game->getCurrentPosComputer().y(), game->getCurrentPosComputer().x());
    // Enable the UI
    enableUI(true);
    // Check for the end of the game
    if (handleGameEnd()) {
        // Now user can change Grid Size and Symbol
        ui->Grid_size->setEnabled(true);
        enableSelectSymbol(true);
    }
}
// Display the winner of the game
/**
 * @brief Display the winner of the game.
 *
 * @param winner The type of player who won the game.
 */
void GameWindow::displayWinner(tictactoe::Player_Type winner)
{
    if (tictactoe::Player_Type::HUMAN == winner) {
        ui->Result_text->setText(tictactoe::PLAYER_WON);
    }
    else{
        ui->Result_text->setText(tictactoe::PLAYER_LOST);
    }
}

// Toggle the board's buttons
/**
 * @brief Toggle the state of the board's buttons.
 *
 * @param enable True to enable the buttons, false to disable.
 * @param resetText True to reset the text of the buttons, false otherwise.
 */
void GameWindow::toggleBoard(bool enable, bool resetText)
{
    try {
        // Iterate over buttons in the layout
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                QWidget* widget = buttonLayout->itemAtPosition(row, col)->widget();
                if (widget && widget->isWidgetType()) {
                    QPushButton* button = qobject_cast<QPushButton*>(widget);
                    if (button) {
                        button->setEnabled(enable);
                        if (resetText) {
                            button->setText("");
                        }
                    }
                }
            }
        }
    }
	catch (const std::exception& e) {
		// Log the exception message
		tictactoe::Logger::getInstance().logError(e.what(), LOG_LOCATION);
	}
}

// Restart the game
/**
 * @brief Restart the game with the specified message.
 *
 * @param msg The message to display when restarting the game.
 */
void GameWindow::Restartgame(QString msg)
{
    try {
        ui->Result_text->setText(msg);
        // always using minimax ai, in future need a ui modification to change AI
        game->startNewGame(symbol, tictactoe::AIType::Minimax, size);
        toggleBoard(true, true);
        enableSelectSymbol(false);
        ui->Grid_size->setEnabled(false);
    }
	catch (const std::exception& e) {
		// Log the exception message
		tictactoe::Logger::getInstance().logError(e.what(), LOG_LOCATION);
	}
}

// Handle the "Start" button click event
/**
 * @brief Handle the click event of the "Start" button.
 */
void GameWindow::on_Start_button_clicked()
{
    Restartgame(tictactoe::CLICK_CELL);
}

// Enable or disable the symbol selection
/**
 * @brief Enable or disable the symbol selection.
 *
 * @param enable True to enable the symbol selection, false to disable.
 */
void GameWindow::enableSelectSymbol(bool enable)
{
    ui->radioButton->setEnabled(enable);
    ui->radioButton_2->setEnabled(enable);
}

// Handle the "X" radio button click event
/**
 * @brief Handle the click event of the "X" radio button.
 */
void GameWindow::on_radioButton_clicked()
{
    symbol = tictactoe::Symbol::X;
}

// Handle the "O" radio button click event
/**
 * @brief Handle the click event of the "O" radio button.
 */
void GameWindow::on_radioButton_2_clicked()
{
    symbol = tictactoe::Symbol::O;
}

// Handle the grid size value change event
/**
 * @brief Handle the value change event of the grid size.
 *
 * @param arg1 The new value of the grid size.
 */
void GameWindow::on_Grid_size_valueChanged(int arg1)
{
    size = arg1;
    createButtons();
    toggleBoard(false, true);
    ui->Result_text->setText(tictactoe::CLICK_START);
}

// Handle the game level value change event
/**
 * @brief Handle the value change event of the game level.
 *
 * @param arg1 The new value of the game level.
 */
void GameWindow::on_Game_level_valueChanged(int arg1)
{
    if (game) {
        game->setGameLevel(static_cast<tictactoe::GameLevel>(arg1));
    }
    else{
		tictactoe::Logger::getInstance().logError("invalid game ptr", LOG_LOCATION);
	}
}

// Enable or disable the user interface elements
/**
 * @brief Enable or disable the user interface elements.
 *
 * @param enable True to enable the UI elements, false to disable.
 */
void GameWindow::enableUI(bool enable)
{
    ui->Game_level->setEnabled(enable);
    toggleBoard(enable, false);
    ui->Start_button->setEnabled(enable);
    ui->Result_text->setEnabled(enable);
    if (!enable){
        ui->Result_text->setText(tictactoe::PC_CALC);
    }
    else{
        ui->Result_text->setText(tictactoe::CLICK_CELL);
    }
}

// Set up the symbol selection radio buttons
/**
 * @brief Set up the symbol selection radio buttons.
 */
void GameWindow::setupSymbolSelection()
{
    try {
        // Create button group and add radio buttons to it
        buttonGroup = new QButtonGroup(this);
        buttonGroup->addButton(ui->radioButton);
        buttonGroup->addButton(ui->radioButton_2);
        ui->radioButton_2->setChecked(true); // default
        ui->radioButton->setChecked(false); // default

        // Set exclusive property to ensure only one button can be selected
        buttonGroup->setExclusive(true);
    }
    catch (const std::exception& e) {
        // Log the exception message
        tictactoe::Logger::getInstance().logError(e.what(), LOG_LOCATION);
    }
}

