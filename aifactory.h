/**
 * @file AIFactory.h
 * @brief Header file for the AIFactory class.
 *
 * This file contains the declaration of the AIFactory class.
 *
 * @author Binu Melit Devassy
 * @date 2024-02-16
 *
 * @license MIT License
 */
    
#ifndef AIFACTORY_H
#define AIFACTORY_H

#include <memory>
#include "gameai.h"

namespace tictactoe{

    /**
    * @brief The AIFactory class.
    */
    class AIFactory{
    public:
        /**
         * @brief Creates an instance of GameAI based on the provided AIType.
         */
        static std::unique_ptr<GameAI> createAI(AIType type);
    };

} // namespace tictactoe

#endif // AIFACTORY_H
