//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_OBSERVERS_H
#define ADVACEDPROGRAMINGZIT2_OBSERVERS_H

#include "BGTile.h"
#include "Player.h"
#include <list>
#include <memory>
#include <vector>

// Forward declarations to avoid circular includes
class World;
class Score;
class Camera;

/**
 * @brief Observer interface for World updates.
 */
class WorldObserver {
public:
    virtual void update(std::weak_ptr<World> world) = 0;
    virtual ~WorldObserver() = default;
};

/**
 * @brief Observer interface for Score updates.
 */
class ScoreObserver {
public:
    virtual void update(std::weak_ptr<Score> score) = 0;
    virtual ~ScoreObserver() = default;
};

/**
 * @brief Observer interface for Camera updates.
 */
class CameraObserver {
public:
    virtual void update(std::weak_ptr<Camera> camera) = 0;
    virtual ~CameraObserver() = default;
};

/**
 * @brief Tracks the current and maximum score of the player.
 *        Applies penalties based on in-game events.
 */
class Score : public WorldObserver, public std::enable_shared_from_this<Score> {
private:
    int minusPoints; ///< Penalty points for repeated actions
    std::list<std::weak_ptr<ScoreObserver>> _observers;
    int maxScore;
    int currentScore;
    float height;

    void updateObservers();

public:
    /**
     * @brief Constructs a Score object.
     */
    Score();

    /**
     * @brief Updates score based on the world state.
     */
    void update(std::weak_ptr<World> world) override;

    /**
     * @brief Adds an observer to this Score.
     */
    void addObserver(const std::shared_ptr<ScoreObserver>& observer);

    /**
     * @brief Gets the current score minus penalties.
     */
    [[nodiscard]] int getCurrentScore() const noexcept;

    /**
     * @brief Gets the highest score reached.
     */
    [[nodiscard]] int getMaxScore() const noexcept;
};

// Type alias for describing a tile’s position and attributes
using tileDescription = std::pair<std::pair<float, float>, std::pair<Tile::Color, Tile::BonusType>>;

/**
 * @brief Represents the camera's view and state.
 *        Normalizes tile/player coordinates and tracks game over.
 */
class Camera : public WorldObserver, public std::enable_shared_from_this<Camera> {
private:
    std::list<std::weak_ptr<CameraObserver>> _observers;
    std::vector<tileDescription> _tileDescription;
    std::pair<float, float> playerCoordinates;
    float height;
    bool gameOver;

    void normalizedCoordinates(float worldHeight);
    void updateObservers();

public:
    /**
     * @brief Constructs a Camera object.
     */
    Camera();

    /**
     * @brief Updates the camera based on the world state.
     */
    void update(std::weak_ptr<World> world) override;

    /**
     * @brief Adds an observer to this Camera.
     */
    void addObserver(const std::shared_ptr<CameraObserver>& observer);

    /**
     * @brief Gets the current visible tiles in screen coordinates.
     */
    [[nodiscard]] const std::vector<tileDescription>& getTileDescription() const noexcept;

    /**
     * @brief Gets the player position in screen coordinates.
     */
    [[nodiscard]] const std::pair<float, float>& getPlayerCoordinates() const noexcept;

    /**
     * @brief Indicates if the player is out of view (game over).
     */
    [[nodiscard]] bool isGameOver() const noexcept;
};

#endif // ADVACEDPROGRAMINGZIT2_OBSERVERS_H