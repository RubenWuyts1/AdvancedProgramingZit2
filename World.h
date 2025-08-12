//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_WORLD_H
#define ADVACEDPROGRAMINGZIT2_WORLD_H

#include <list>
#include "BGTileFactory.h"
#include "Observers.h"
#include "Random.h"
#include "Stopwatch.h"

/**
 * @brief Player movement direction.
 */
enum class Direction {
    None, Left, Right
};

/**
 * @brief Handles game logic: player, tiles, collisions, and observers.
 */
class World : public std::enable_shared_from_this<World> {
private:
    bool lastJumpedOn = false;
    Tile::BGTile *lastJumpedOnTile = nullptr;

    std::list<std::shared_ptr<WorldObserver>> _observers;
    std::unique_ptr<Tile::Factory::BGTileFactory> tileFactory;
    std::vector<std::unique_ptr<Tile::BGTile>> tiles;
    std::unique_ptr<Player> player;

    const float PlatformSizeX;
    const float PlatformSizeY;
    const float maxWidth;
    const float maxHeight;

    float maxDifY;
    float minDifY;
    float worldOffSetY = 0.0f;
    unsigned int maxAmountOfTiles;

    struct TileSpawnChances {
        int white, blue, yellow, green;
    };

    // Internal logic
    [[nodiscard]] TileSpawnChances getSpawnChances(int height) const;

    [[nodiscard]] std::pair<float, float> getFreePosInitialization() const;

    void updateObservers();

    [[nodiscard]] bool isValid(int y) const noexcept;

    void removeTile(const Tile::BGTile *targetTile) noexcept;

    [[nodiscard]] float getHighestTileY() const noexcept;

    // Logic split from update()
    void handlePlayerInput(double dt, Direction moveInput);

    void updateAllTiles();

    void scrollCameraIfNeeded();

    void spawnTileIfNeeded();

    void handleTileCollisions();

public:
    /**
     * @brief Creates the world with a tile factory.
     */
    explicit World(std::unique_ptr<Tile::Factory::BGTileFactory> factory);

    /**
     * @brief Updates game logic.
     */
    void update(double dt, Direction moveInput);

    /**
     * @brief Initializes player and tiles.
     */
    void initializeWorld(const std::shared_ptr<World> &self);

    /**
     * @brief Adds an observer.
     */
    void addObserver(const std::shared_ptr<WorldObserver> &observer);

    /// @return True if player jumped on same tile again.
    [[nodiscard]] inline bool isLastJumpedOn() const noexcept { return lastJumpedOn; }

    /// @return Current world vertical offset.
    [[nodiscard]] inline float getWorldOffSetY() const noexcept { return worldOffSetY; }

    /// @return Fixed max screen height.
    [[nodiscard]] inline float getMaxHeight() const noexcept { return maxHeight; }

    /// @return Highest Y the player has reached.
    [[nodiscard]] inline float getMaxPlayerHeight() const noexcept { return player->getMaxHeight(); }

    /// @return All active tiles.
    [[nodiscard]] inline const std::vector<std::unique_ptr<Tile::BGTile>> &getTiles() const noexcept {
        return tiles;
    }

    /// @return Player position (x, y).
    [[nodiscard]] inline std::pair<float, float> getPlayerPos() const noexcept {
        return {player->getX(), player->getY()};
    }
};

#endif //ADVACEDPROGRAMINGZIT2_WORLD_H