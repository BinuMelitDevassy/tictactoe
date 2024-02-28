/**
 * @file Logger.h
 * @brief Header file for the Logger class.
 *
 * This file contains the declaration of the Logger class, which provides logging functionality.
 * The Logger class is a singleton and can be used to log informational and error messages.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


namespace tictactoe {


// Macro to get the file name and line number
#define LOG_LOCATION ((std::ostringstream() << __FILE__ << ":" << __LINE__).str())

    /**
     * @brief The Logger class used to log the errors in the Tic Tac Toe game.
     */
    class Logger {
    public:
        /**
         * @brief Get the single instance of the Logger.
         *
         * @return Reference to the Logger instance.
         */
        inline static Logger& getInstance() {
            static Logger instance; // The one and only Logger object
            return instance;
        }

        //need to include lock.. lllll
        /**
         * @brief Logs an informational message with optional location information.
         *
         * @param message The informational message to log.
         * @param location Optional location information to include in the log message.
         */
        inline void logInfo(const std::string& message, const std::string& location = "") {
            std::cout << "[INFO] " << (location.empty() ? "" : location + " ") << message << std::endl;
        }
        /**
         * @brief Logs an error message with optional location information.
         *
         * @param message The error message to log.
         * @param location Optional location information to include in the log message.
         */
        inline void logError(const std::string& message, const std::string& location = "") {
            std::cout << "[ERROR] " << (location.empty() ? "" : location + " ") << message << std::endl;
        }

    private:
        // Private constructor to prevent external instantiation
        Logger() {}

        // Private copy constructor, assignment operators, move constructor, and move assignment operator to prevent copies and moves
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;
    };
}
#endif // LOGGER_H
