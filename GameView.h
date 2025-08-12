//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_GAMEVIEW_H
#define ADVACEDPROGRAMINGZIT2_GAMEVIEW_H

#include "Observers.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "World.h"
#include <iostream>

/**
 * @brief Visual representation of the game.
 *        Renders the player, tiles, background, score, and game-over screen.
 *        Listens to updates from Camera and Score.
 */
class GameView : public CameraObserver, public ScoreObserver {
private:
    sf::RenderWindow& window; ///< Reference to the main game window

    // Platform rendering
    sf::Sprite platform;
    sf::Texture platformTextureGreen;
    sf::Texture platformTextureBlue;
    sf::Texture platformTextureWhite;
    sf::Texture platformTextureYellow;

    // Bonus items
    sf::Texture springTexture;
    sf::Sprite spring;
    sf::Texture jetpackTexture;
    sf::Sprite jetpack;

    // Backgrounds
    sf::Texture GameOverBackgroundTexture;
    sf::Sprite GameOverBackground;
    sf::Sprite Background;
    sf::Texture BackgroundTexture;

    // Score text
    sf::Font font;
    sf::Text scoreText;
    sf::Text scoreGameOverText;

    // Player rendering
    sf::Sprite Player;
    sf::Texture PlayerTexture;

    std::vector<tileDescription> renderTiles; ///< Tiles to draw from camera
    std::pair<float, float> playerPos;        ///< Player screen position
    bool gameOver = false;                    ///< Game over flag

    /**
     * @brief Draws the game-over screen and score.
     */
    void drawGameOverBackground();

public:
    /**
     * @brief Constructs the GameView and loads all assets.
     * @param win Reference to the SFML render window.
     */
    explicit GameView(sf::RenderWindow& win);

    /**
     * @brief Updates the score display from Score observer.
     * @param score Weak pointer to the Score instance.
     */
    void update(std::weak_ptr<Score> score) override;

    /**
     * @brief Updates tile and player data from the Camera.
     * @param camera Weak pointer to the Camera instance.
     */
    void update(std::weak_ptr<Camera> camera) override;

    /**
     * @brief Renders the game screen (player, background, tiles, score).
     */
    void draw();
};

#endif // ADVACEDPROGRAMINGZIT2_GAMEVIEW_H