//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_GAME_H
#define ADVACEDPROGRAMINGZIT2_GAME_H

#include "GameView.h"
#include "Singletons.h"
#include "Observers.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Game {
private:
    DefaultBGTileFactory tileFactory;
    std::shared_ptr<World> world;
    std::shared_ptr<GameView> view;
    std::shared_ptr<Score> score;
    std::shared_ptr<Camera> camera;
    sf::RenderWindow window;
public:
    virtual ~Game();

public:
    Game();
    void run();
};


#endif //ADVACEDPROGRAMINGZIT2_GAME_H
