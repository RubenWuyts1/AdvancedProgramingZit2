//
// Created by ruben on 23/07/25.
//

#include "World.h"
#include <iostream>

using util::randomValue;

/**
 * @brief Constructor: initialize world parameters and factory.
 */
World::World(std::unique_ptr<Tile::Factory::BGTileFactory> factory)
    : tileFactory(std::move(factory)), PlatformSizeX(68), lastJumpedOn(false), lastJumpedOnTile(nullptr),
      PlatformSizeY(14), maxHeight(700.f), maxWidth(500.f), worldOffSetY(0), minDifY(25), maxDifY(225),
      maxAmountOfTiles(12) {}

/**
 * @brief Main update function: delegates world logic.
 */
void World::update(double dt, Direction moveInput) {
    handlePlayerInput(dt, moveInput); // move player based on input
    updateAllTiles();                 // update all tile positions (e.g., moving platforms)
    scrollCameraIfNeeded();           // move camera if player reaches top
    spawnTileIfNeeded();              // add new tiles if needed
    handleTileCollisions();           // handle collisions and jumping
    updateObservers();                // notify observers (e.g., view, score)
}

/**
 * @brief Handles player movement input and vertical update.
 */
void World::handlePlayerInput(double dt, Direction moveInput) {
    float movementX = 0;
    if (moveInput == Direction::Right) {
        movementX = 300;
    } else if (moveInput == Direction::Left) {
        movementX = -300;
    }
    float dx = movementX * static_cast<float>(dt);
    player->moveHorizontally(dx);
    player->moveVertically(dt, worldOffSetY);
}

/**
 * @brief Updates all existing tiles.
 */
void World::updateAllTiles() {
    for (auto& tile : tiles) {
        tile->update(maxWidth, PlatformSizeX);
    }
}

/**
 * @brief Scrolls the world up when player reaches top.
 *        Removes off-screen tiles below.
 */
void World::scrollCameraIfNeeded() {
    if (player->playerOnMaxHeight()) {
        worldOffSetY -= maxHeight / 1.25;
        for (size_t i = 0; i < tiles.size();) {
            if (tiles[i]->getPosY() < worldOffSetY) {
                tiles.erase(tiles.begin() + i);
            } else {
                ++i;
            }
        }
    }
}

/**
 * @brief Spawns a new tile above the screen when spacing allows or too few tiles exist.
 */
void World::spawnTileIfNeeded() {
    int maxPlayerHeight = static_cast<int>(player->getMaxHeight());
    maxAmountOfTiles = std::max(5, 12 - (maxPlayerHeight / 10000));

    if (tiles.size() < maxAmountOfTiles || maxDifY < worldOffSetY + maxHeight - getHighestTileY()) {

        auto chances = getSpawnChances(maxPlayerHeight);
        int roll = util::randomValue(1, 100);
        int posX = util::randomFloat(0, maxWidth - PlatformSizeX);
        float posY = worldOffSetY + maxHeight;

        // Determine tile type based on spawn chances
        if (roll <= chances.white) {
            tiles.emplace_back(tileFactory->createWhite(posX, posY));
        } else if (roll <= chances.white + chances.blue) {
            tiles.emplace_back(tileFactory->createBlue(posX, posY));
        } else if (roll <= chances.white + chances.blue + chances.yellow) {
            tiles.emplace_back(tileFactory->createYellow(posX, posY));
        } else {
            tiles.emplace_back(tileFactory->createGreen(posX, posY));
        }
    }
}

/**
 * @brief Handles collision detection and jump logic.
 */
void World::handleTileCollisions() {
    float playerX = player->getX();
    float playerY = player->getY();
    float playerSpeed = player->getSpeed();
    lastJumpedOn = false;

    for (const auto& tile : tiles) {
        float tileX = tile->getPosX();

        // Simple AABB collision and downward motion check
        bool falling = playerSpeed < 0;
        bool withinX = (playerX + player->getPlayerWidth() > tileX) && (playerX < tileX + PlatformSizeX);
        bool passedThrough = tile->getPosY() + 5 > playerY && tile->getPosY() - PlatformSizeY - 10 < playerY;

        if (passedThrough && falling && withinX) {
            if (lastJumpedOnTile != nullptr && lastJumpedOnTile == tile.get()) {
                lastJumpedOn = true;
            }

            // Apply bonus jump value
            player->jump(tile->getBonusValue());

            if (tile->getColor() == Tile::Color::White) {
                removeTile(tile.get()); // Disappearing platform
                lastJumpedOnTile = nullptr;
            } else {
                lastJumpedOnTile = tile.get();
            }
            break;
        }
    }
}

/**
 * @brief Initializes the world: creates player and platforms.
 */
void World::initializeWorld(const std::shared_ptr<World>& self) {
    player = std::make_unique<Player>(maxWidth / 2.4f, 50, 50, 80, maxWidth);
    tiles.emplace_back(tileFactory->createGreen(maxWidth / 2.4f, 25));

    for (int i = 0; i < maxAmountOfTiles; ++i) {
        auto pos = getFreePosInitialization();
        tiles.emplace_back(tileFactory->createGreen(pos.first, pos.second));
    }

    updateObservers();
}

/**
 * @brief Generates a random (X, Y) spawn position for tiles.
 */
std::pair<float, float> World::getFreePosInitialization() const {
    int posX = randomValue(0, std::floor(maxWidth) - PlatformSizeX);
    int posY = randomValue(-200, std::floor(maxHeight));
    while (!isValid(posY)) {
        posY = randomValue(0, std::floor(maxHeight));
    }
    return {posX, posY};
}

/**
 * @brief Checks if Y-position is valid based on distance to other tiles.
 */
bool World::isValid(int y) const noexcept {
    bool maxDif = false;
    for (const auto& tile : tiles) {
        if (std::abs(y - tile->getPosY()) < minDifY) {
            return false;
        }
        if (std::abs(y - tile->getPosY()) < maxDifY) {
            maxDif = true;
        }
    }
    return maxDif;
}

/**
 * @brief Returns the highest Y-position among all tiles.
 */
float World::getHighestTileY() const noexcept {
    float highest = 0.0f;
    for (const auto& tile : tiles) {
        highest = std::max(highest, tile->getPosY());
    }
    return highest;
}

/**
 * @brief Notifies all observers with the current world state.
 */
void World::updateObservers() {
    auto self = shared_from_this();
    for (const auto& observer : _observers) {
        observer->update(self);
    }
}

/**
 * @brief Adds a world observer (e.g., view or score system).
 */
void World::addObserver(const std::shared_ptr<WorldObserver>& observer) { _observers.push_back(observer); }

/**
 * @brief Removes a tile from the world (by pointer comparison).
 */
void World::removeTile(const Tile::BGTile* targetTile) noexcept {
    auto it = std::remove_if(tiles.begin(), tiles.end(), [targetTile](const std::unique_ptr<Tile::BGTile>& tile) {
        return tile.get() == targetTile;
    });
    if (it != tiles.end()) {
        tiles.erase(it, tiles.end());
    }
}

/**
 * @brief Calculates spawn probabilities for tile types based on player height.
 */
World::TileSpawnChances World::getSpawnChances(int height) const {
    int white = std::min(25, 10 + (height / 10000) * 5);
    int blue = std::min(35, 10 + (height / 10000) * 5);
    int yellow = std::min(20, 5 + (height / 15000) * 5);
    int total = white + blue + yellow;
    int green = std::max(0, 100 - total); // remainder

    return {white, blue, yellow, green};
}
