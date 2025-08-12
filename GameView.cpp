//
// Created by ruben on 23/07/25.
//

#include "GameView.h"

/**
 * @brief Constructs the GameView and loads all textures, fonts, and sets default visuals.
 * @throws std::runtime_error if any file fails to load.
 */
GameView::GameView(sf::RenderWindow& win) : window(win), gameOver(false), playerPos{}, renderTiles{} {
    try {
        // Load all platform textures
        if (!platformTextureGreen.loadFromFile("../Media/platform_green.png"))
            throw std::runtime_error("Failed to load platform texture (green)");
        if (!platformTextureBlue.loadFromFile("../Media/platform_blue.png"))
            throw std::runtime_error("Failed to load platform texture (blue)");
        if (!platformTextureYellow.loadFromFile("../Media/platform_yellow.png"))
            throw std::runtime_error("Failed to load platform texture (yellow)");
        if (!platformTextureWhite.loadFromFile("../Media/platform_white.png"))
            throw std::runtime_error("Failed to load platform texture (white)");

        // Load player and background textures
        if (!PlayerTexture.loadFromFile("../Media/doodle.png"))
            throw std::runtime_error("Failed to load player texture");
        if (!BackgroundTexture.loadFromFile("../Media/clean_game_background.png"))
            throw std::runtime_error("Failed to load background texture");
        if (!GameOverBackgroundTexture.loadFromFile("../Media/game_over_background_final.png"))
            throw std::runtime_error("Failed to load game over background texture");

        // Load bonus textures
        if (!springTexture.loadFromFile("../Media/spring.png"))
            throw std::runtime_error("Failed to load spring texture");
        if (!jetpackTexture.loadFromFile("../Media/jetPack.png"))
            throw std::runtime_error("Failed to load jetpack texture");

        // Load font
        if (!font.loadFromFile("../Media/arial.ttf"))
            throw std::runtime_error("Failed to load font");
    } catch (const std::exception& e) {
        std::cerr << "Exception in GameView constructor: " << e.what() << std::endl;
        throw; // rethrow to fail-fast
    }

    // Set default textures and text properties
    platform.setTexture(platformTextureGreen);
    Player.setTexture(PlayerTexture);
    Background.setTexture(BackgroundTexture);
    GameOverBackground.setTexture(GameOverBackgroundTexture);
    spring.setTexture(springTexture);
    jetpack.setTexture(jetpackTexture);

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(50, 25);

    scoreGameOverText.setFont(font);
    scoreGameOverText.setCharacterSize(65);
    scoreGameOverText.setFillColor(sf::Color::Red);
    scoreGameOverText.setPosition(65, 100);
}

/**
 * @brief Updates the visible score text based on current and max score.
 * @param score Weak pointer to the Score object.
 */
void GameView::update(std::weak_ptr<Score> score) {
    if (auto scoreShared = score.lock()) {
        std::string scoreStr = "Score: " + std::to_string(scoreShared->getCurrentScore());
        scoreText.setString(scoreStr);

        std::string scoreMaxStr = "Score: " + std::to_string(scoreShared->getMaxScore());
        scoreGameOverText.setString(scoreMaxStr);
    }
}

/**
 * @brief Updates the player and tile data from the Camera.
 * @param camera Weak pointer to the Camera object.
 */
void GameView::update(std::weak_ptr<Camera> camera) {
    if (auto cameraShared = camera.lock()) {
        gameOver = cameraShared->isGameOver();
        renderTiles = cameraShared->getTileDescription();
        playerPos = cameraShared->getPlayerCoordinates();
    }
}

/**
 * @brief Renders the game screen.
 *        Draws background, player, tiles, bonuses, and score.
 *        If game is over, displays game over screen.
 */
void GameView::draw() {
    if (gameOver) {
        drawGameOverBackground();
        return;
    }

    // Position the player slightly above center
    Player.setPosition(playerPos.first, playerPos.second - 75);

    window.draw(Background);
    window.draw(Player);
    window.draw(scoreText);

    // Draw all visible tiles and attached bonuses
    for (const auto& tile : renderTiles) {
        float x = tile.first.first;
        float y = tile.first.second;

        platform.setPosition(x, y);

        // Set platform texture based on color
        switch (tile.second.first) {
        case Tile::Color::Green:
            platform.setTexture(platformTextureGreen);
            break;
        case Tile::Color::Blue:
            platform.setTexture(platformTextureBlue);
            break;
        case Tile::Color::Yellow:
            platform.setTexture(platformTextureYellow);
            break;
        case Tile::Color::White:
            platform.setTexture(platformTextureWhite);
            break;
        }

        // Draw bonus if present
        switch (tile.second.second) {
        case Tile::BonusType::Spring:
            spring.setPosition(x + 17, y - 20);
            window.draw(spring);
            break;
        case Tile::BonusType::Jetpack:
            jetpack.setPosition(x + 17, y - 40);
            window.draw(jetpack);
            break;
        default:
            break;
        }

        window.draw(platform);
    }
}

/**
 * @brief Draws the game over screen with final score.
 */
void GameView::drawGameOverBackground() {
    window.draw(GameOverBackground);
    window.draw(scoreGameOverText);
}