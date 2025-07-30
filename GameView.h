//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_GAMEVIEW_H
#define ADVACEDPROGRAMINGZIT2_GAMEVIEW_H


#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "World.h"
#include "Observers.h"

class GameView : public CameraObserver, public ScoreObserver {
private:
    sf::RenderWindow& window;

    sf::Sprite platform;
    sf::Texture platformTextureGreen;
    sf::Texture platformTextureBlue;
    sf::Texture platformTextureWhite;
    sf::Texture platformTextureYellow;

    sf::Texture springTexture;
    sf::Sprite spring;
    sf::Texture jetpackTexture;
    sf::Sprite jetpack;

    sf::Texture GameOverBackgroundTexture;
    sf::Sprite GameOverBackground;
    sf::Sprite Background;
    sf::Texture BackgroundTexture;

    sf::Font font;
    sf::Text scoreText;
    sf::Text scoreGameOverText;

    sf::Sprite Player;
    sf::Texture PlayerTexture;
    std::vector<tileDescription> renderTiles;
    std::pair<float, float> playerPos;
    bool gameOver;
    void drawGameOverBackground();
public:
    explicit GameView(sf::RenderWindow& win);
    void update(std::weak_ptr<Score> score) override;
    void update(std::weak_ptr<Camera> camera) override;
    void draw();
};


#endif //ADVACEDPROGRAMINGZIT2_GAMEVIEW_H
