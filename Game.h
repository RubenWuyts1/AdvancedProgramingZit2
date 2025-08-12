//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_GAME_H
#define ADVACEDPROGRAMINGZIT2_GAME_H

#include "GameView.h"
#include "Observers.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Stopwatch.h"

namespace Controller {
/**
 * @class Game
 * @brief Manages the main game loop, input handling, updates, and rendering.
 */
class Game {
private:
    /**
     * @brief Sets up observer connections between model and view.
     */
    void setupObservers() noexcept;
    /**
     * @brief Handles window events and keyboard input.
     */
    void handleEvents();
    /**
     * @brief Updates the world state based on input and time.
     */
    void update();
    /**
     * @brief Draws the current game state to the window.
     */
    void render();
    Direction direction = Direction::None;
    std::shared_ptr<World> world;
    std::shared_ptr<GameView> view;
    std::shared_ptr<Score> score;
    std::shared_ptr<Camera> camera;
    sf::RenderWindow window;

public:
    /**
     * @brief Constructs and initializes the game.
     */
    Game();
    /**
     * @brief Deleted copy constructor.
     */
    Game(const Game&) = delete;
    /**
     * @brief Deleted copy assignment operator.
     */
    Game& operator=(const Game&) = delete;
    /**
     * @brief Starts the main game loop.
     */
    void run();
};
} // namespace Controller

#endif // ADVACEDPROGRAMINGZIT2_GAME_H