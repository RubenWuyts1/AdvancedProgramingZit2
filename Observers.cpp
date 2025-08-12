//
// Created by ruben on 23/07/25.
//

#include "Observers.h"
#include "World.h"
#include <cmath>
#include <iostream>

/// Constant screen height used for game-over detection
constexpr int screenHeight = 700;

/**
 * @brief Constructs a Score object.
 * Initializes all internal counters to zero.
 */
Score::Score() : height{0}, maxScore{0}, currentScore{0}, minusPoints{0} {}

/**
 * @brief Updates the score based on the world state.
 * Applies penalties and updates observers.
 * @param world Weak pointer to the current World instance.
 */
void Score::update(std::weak_ptr<World> world) {
    if (auto worldShared = world.lock()) {
        currentScore = worldShared->getMaxPlayerHeight() - 50;

        // Update max score if new high (minus penalties)
        if ((currentScore - minusPoints) > maxScore) {
            maxScore = currentScore - minusPoints;
        }

        // Penalty for reusing the same platform
        if (worldShared->isLastJumpedOn()) {
            minusPoints += 250;
        }

        updateObservers();
    }
}

/**
 * @brief Adds a ScoreObserver to be notified on changes.
 */
void Score::addObserver(const std::shared_ptr<ScoreObserver>& observer) { _observers.push_back(observer); }

/**
 * @brief Notifies all active ScoreObservers of an update.
 * Removes expired (dead) observers.
 */
void Score::updateObservers() {
    for (auto it = _observers.begin(); it != _observers.end();) {
        if (auto obs = it->lock()) {
            obs->update(shared_from_this());
            ++it;
        } else {
            it = _observers.erase(it); // Clean up expired observers
        }
    }
}

/**
 * @brief Gets the current score minus penalties.
 * @return Final score to display.
 */
[[nodiscard]] int Score::getCurrentScore() const noexcept { return currentScore - minusPoints; }

/**
 * @brief Gets the highest score ever reached.
 * @return Max score (with penalties already applied).
 */
[[nodiscard]] int Score::getMaxScore() const noexcept { return maxScore; }

/**
 * @brief Constructs a Camera instance.
 */
Camera::Camera() : playerCoordinates{0.0f, 0.0f}, height{0.0f}, gameOver(false) {}

/**
 * @brief Updates the camera’s state based on world state.
 * Captures tile positions and transforms them to screen coordinates.
 * @param world Weak pointer to the current World instance.
 */
void Camera::update(std::weak_ptr<World> world) {
    if (auto worldShared = world.lock()) {
        _tileDescription.clear();

        // Store raw data from the world
        playerCoordinates = worldShared->getPlayerPos();
        height = worldShared->getWorldOffSetY();

        for (const auto& tile : worldShared->getTiles()) {
            _tileDescription.emplace_back(std::make_pair(std::make_pair(tile->getPosX(), tile->getPosY()),
                                                         std::make_pair(tile->getColor(), tile->getBonusType())));
        }

        // Normalize to screen coordinates
        normalizedCoordinates(worldShared->getMaxHeight());

        // Notify the view
        updateObservers();
    }
}

/**
 * @brief Translates world coordinates to screen-relative coordinates.
 * Also checks for game over (player below screen).
 * @param worldHeight The maximum visible height of the screen.
 */
void Camera::normalizedCoordinates(float worldHeight) {
    for (auto& tile : _tileDescription) {
        tile.first.second -= height;
        tile.first.second = worldHeight - tile.first.second;
    }

    playerCoordinates.second -= height;
    playerCoordinates.second = worldHeight - playerCoordinates.second;

    if (playerCoordinates.second > screenHeight) {
        gameOver = true;
    }
}

/**
 * @brief Registers a CameraObserver for this camera.
 */
void Camera::addObserver(const std::shared_ptr<CameraObserver>& observer) { _observers.push_back(observer); }

/**
 * @brief Notifies all CameraObservers of a camera update.
 * Cleans up expired observers.
 */
void Camera::updateObservers() {
    for (auto it = _observers.begin(); it != _observers.end();) {
        if (auto obs = it->lock()) {
            obs->update(shared_from_this());
            ++it;
        } else {
            it = _observers.erase(it);
        }
    }
}

/**
 * @brief Returns the current tile data in screen-relative coordinates.
 */
[[nodiscard]] const std::vector<tileDescription>& Camera::getTileDescription() const noexcept {
    return _tileDescription;
}

/**
 * @brief Returns the player’s current screen-relative position.
 */
[[nodiscard]] const std::pair<float, float>& Camera::getPlayerCoordinates() const noexcept { return playerCoordinates; }

/**
 * @brief Indicates whether the player has fallen below the screen.
 */
[[nodiscard]] bool Camera::isGameOver() const noexcept { return gameOver; }