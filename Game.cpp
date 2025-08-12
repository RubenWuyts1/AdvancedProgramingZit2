//
// Created by ruben on 23/07/25.
//

#include "Game.h"

// Constructor: Initializes the game window and all core components
Controller::Game::Game()
    : window(sf::VideoMode(500, 700), "Doodle Jump"), score(std::make_shared<Score>()),
      camera(std::make_shared<Camera>()), world(std::make_shared<World>(std::make_unique<Tile::Factory::DefaultBGTileFactory>())),
      view(std::make_shared<GameView>(window)) {

    window.setFramerateLimit(60);  // Cap framerate to 60 FPS
    setupObservers();              // Link model to view components
    world->initializeWorld(world); // Generate initial world state
}

// Connects model observers (camera, score) to view
void Controller::Game::setupObservers() noexcept {
    world->addObserver(score);
    world->addObserver(camera);
    camera->addObserver(view);
    score->addObserver(view);
}

// Main game loop: handles input, updates game state, and renders frame
void Controller::Game::run() {
    while (window.isOpen()) {
        handleEvents(); // Process keyboard and window input
        update();       // Advance game state
        render();       // Draw current state to screen
    }
}

// Handles window events and keyboard input
void Controller::Game::handleEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close(); // Close the window when requested
    }

    direction = Direction::None; // Default input direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        direction = Direction::Left;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction = Direction::Right;
    }
}

// Updates the world state based on delta time and player input
void Controller::Game::update() {
    double deltaTime = util::Stopwatch::getInstance()->tick(); // Time since last frame
    world->update(deltaTime, direction);                 // Forward input and time to world
}

// Clears the window and draws the current view
void Controller::Game::render() {
    window.clear();   // Prepare frame
    view->draw();     // Draw all visual elements
    window.display(); // Present frame
}