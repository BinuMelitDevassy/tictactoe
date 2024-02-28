/**
 * @file main.cpp
 * @brief Implementation file for the main.cpp.
 *
 * This file contains the implementation of the main.cpp, which is the entry point of the Tic-Tac-Toe application.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 */

#include "gamewindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

 /**
  * @brief The main function of the Tic-Tac-Toe application.
  *
  * @param argc The number of command-line arguments.
  * @param argv The array of command-line arguments.
  * @return int The exit code of the application.
  */
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // Load translations based on the system language
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages) {
        const QString baseName = "TicTacToe_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Create and show the main game window
    GameWindow w;
    w.show();

    // Execute the application event loop
    return a.exec();
}
