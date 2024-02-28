/**
 * @file AIFactory.cpp
 * @brief Implementation file for the AIFactory class.
 *
 * This file contains the implementation of the AIFactory class.
 * It provides a factory method to create instances of different AI types.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */

#include "aifactory.h"
#include "minimaxai.h"
#include "randomai.h"

namespace tictactoe {

    /**
     * @brief Create an instance of GameAI based on the given type.
     *
     * @param type The type of AI to create.
     * @return std::unique_ptr<GameAI> A unique pointer to the created AI instance.
     */
    std::unique_ptr<GameAI> AIFactory::createAI(AIType type) {
        switch (type) {
        case AIType::Random: // Random AI
            return std::make_unique<RandomAI>();
        case AIType::Minimax: // Minimax AI
            return std::make_unique<MinimaxAI>();
        default:
            Logger::getInstance().logError("Invalid AI Type", LOG_LOCATION);
            return nullptr;
        }
    }

}  // namespace tictactoe
