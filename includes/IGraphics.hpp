/*
** EPITECH PROJECT, 2023
** Arcade-Architecture
** File description:
** IGraphics
*/

#ifndef IGRAPHICS_HPP
#define IGRAPHICS_HPP
#include <memory>
#include "IObject.hpp"

namespace arcade
{
    class IGraphics
    {
    public:
        virtual ~IGraphics() = default;

        /**
         * @brief Enumerate the possible actions in the arcarde box
         *
         */

        /**
         * @brief Display elements from the current loaded graphic library
         *
         * @return void
         */
        virtual void display() = 0;

        /**
         * @brief Clear current loaded library window from its drawed elements
         *
         * @return void
         */
        virtual void clear() = 0;

        /**
         * @brief Draw object on the scene from the current
         * @params arcade::IObject to be draw in the current graphic library
         * @return void
         */
        virtual void draw(std::shared_ptr<arcade::IObject> object) = 0;

        /**
         * @brief Handle events from the current loaded graphic library
         *
         * @return arcade::Input corresponds to the last events from the loaded graphic library
         */
        virtual arcade::Input event() = 0;
    };
}

#endif