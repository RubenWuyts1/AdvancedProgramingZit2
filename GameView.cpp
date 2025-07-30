//
// Created by ruben on 23/07/25.
//

#include "GameView.h"

GameView::GameView(sf::RenderWindow &win) : window(win), gameOver(false), playerPos{}, renderTiles{} {
    try {
        if (!platformTextureGreen.loadFromFile("../Media/platform_green.png")) {
            throw std::runtime_error("Failed to load platform texture (green)");
        }
        if (!platformTextureBlue.loadFromFile("../Media/platform_blue.png")) {
            throw std::runtime_error("Failed to load platform texture (blue)");
        }
        if (!platformTextureYellow.loadFromFile("../Media/platform_yellow.png")) {
            throw std::runtime_error("Failed to load platform texture (yellow)");
        }
        if (!platformTextureWhite.loadFromFile("../Media/platform_white.png")) {
            throw std::runtime_error("Failed to load platform texture (white)");
        }
        if (!PlayerTexture.loadFromFile("../Media/doodle.png")) {
            throw std::runtime_error("Failed to load player texture");
        }
        if (!BackgroundTexture.loadFromFile("../Media/clean_game_background.png")) {
            throw std::runtime_error("Failed to load background texture");
        }
        if (!GameOverBackgroundTexture.loadFromFile("../Media/game_over_background_final.png")) {
            throw std::runtime_error("Failed to load game over background texture");
        }
        if (!springTexture.loadFromFile("../Media/spring.png")) {
            throw std::runtime_error("Failed to load spring texture");
        }
        if (!jetpackTexture.loadFromFile("../Media/jetPack.png")) {
            throw std::runtime_error("Failed to load jetpack texture");
        }
        if (!font.loadFromFile("../Media/arial.ttf")) {
            throw std::runtime_error("Failed to load font");
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in GameView constructor: " << e.what() << std::endl;

        throw;
    }
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

void GameView::update(std::weak_ptr<Score> score) {
    if (auto scoreShared = score.lock()) {
        std::string s = "Score: " + std::to_string(scoreShared->getCurrentScore());
        scoreText.setString(s);
        std::string gameOverS = "Score: " + std::to_string(scoreShared->getMaxScore());
        scoreGameOverText.setString(gameOverS);
    }
}

void GameView::update(std::weak_ptr<Camera> camera) {
    if (auto cameraShared = camera.lock()) {
        gameOver = cameraShared->isGameOver();
        renderTiles = cameraShared->getTileDescription();
        playerPos = cameraShared->getPlayerCoordinates();
    }
}

void GameView::draw() {
    window.clear();
    if (gameOver) {
        drawGameOverBackground();
        return;
    }
    Player.setPosition(playerPos.first, playerPos.second-75);
    window.draw(Background);
    window.draw(Player);
    window.draw(scoreText);
    for (const auto& tile : renderTiles) {
        platform.setPosition(tile.first.first, tile.first.second);
        if (tile.second.first == Color::Green) {
            platform.setTexture(platformTextureGreen);
        } else if (tile.second.first == Color::Blue) {
            platform.setTexture(platformTextureBlue);
        } else if (tile.second.first == Color::Yellow) {
            platform.setTexture(platformTextureYellow);
        } else if (tile.second.first == Color::White) {
            platform.setTexture(platformTextureWhite);
        }
        if (tile.second.second == BonusType::Spring) {
            spring.setPosition(tile.first.first+17, tile.first.second-20);
            window.draw(spring);
        } else if (tile.second.second == BonusType::Jetpack) {
            jetpack.setPosition(tile.first.first+17, tile.first.second-40);
            window.draw(jetpack);
        }
        window.draw(platform);
    }
    window.display();
}

void GameView::drawGameOverBackground() {
    window.draw(GameOverBackground);
    window.draw(scoreGameOverText);
    window.display();
}
