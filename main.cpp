#include "Game.h" // Zorg dat deze header Controller::Game bevat

/**
 * @brief Entry point of the Doodle Jump game.
 *
 * Initializes and runs the main game loop using the Game controller.
 *
 * @return Exit code (0 = success)
 */
int main() {
    Controller::Game g; ///< Instantiate the game controller
    g.run();            ///< Start the main game loop
    return 0;           ///< Exit normally
}