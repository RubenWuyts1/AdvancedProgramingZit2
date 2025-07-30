//
// Created by ruben on 23/07/25.
//

#include "Game.h"


Game::Game() : window(sf::VideoMode(500, 700), "Doodle Jump") {

    // Zet framerate cap (optioneel)
    window.setFramerateLimit(60);
    // Maak modellen aan
    score = std::make_shared<Score>();
    camera = std::make_shared<Camera>();

    // Geef camera en score als observer-onderdelen door aan factory
    auto factory = std::make_unique<DefaultBGTileFactory>();  // Of: je maakt deze ook observer-aware

    // Maak wereld aan met factory
    world = std::make_shared<World>(std::move(factory));

    // Koppel World → Score en Camera als observers
    world->addObserver(score);
    world->addObserver(camera);
    // Maak GameView aan met toegang tot alles wat hij moet weergeven
    view = std::make_shared<GameView>(window);

    // Koppel Camera en Score → GameView als observer
    camera->addObserver(view);
    score->addObserver(view);

    world->initializeWorld(world);
}

void Game::run() {
    Direction direction = Direction::None;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        double deltaTime = Stopwatch::getInstance()->tick();
        direction = Direction::None;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            direction = Direction::Left;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction = Direction::Right;
        }
        world->update(deltaTime, direction);
        window.clear();
        view->draw(); // View tekent op basis van model
        window.display();
    }
}

Game::~Game() {
    if (window.isOpen()) {
        window.close();
    }
}
