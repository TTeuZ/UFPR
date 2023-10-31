#ifndef GAME_HPP
#define GAME_HPP

#include "../Functionals/Display/Display.hpp"

class Game {
   public:
    /**
     * Instanciate an Game object, that will contain all the information
     * necessary to play the game
     *
     * @param width Game display width
     * @param height Game DIsplay height
     */
    Game(const Display& display);

   private:
    Display& display;
};

#endif