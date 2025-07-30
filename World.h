//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_WORLD_H
#define ADVACEDPROGRAMINGZIT2_WORLD_H

#include <list>
#include "BGTile.h"
#include "Observers.h"
#include "Singletons.h"

enum class Direction{None, Left, Right};

class Player {
private:
    float x;
    float y;
    float maxY;
    float speed;
    const float playerWidth;
    const float playerHeight;
    const float worldWidth;
public:
    Player(float x, float y, float playerWidth, float playerHeight, float worldWidth);

    void moveVertically(double dt, float& worldOffSet) noexcept;

    [[nodiscard]] float getX() const noexcept {return x;}

    [[nodiscard]] float getY() const noexcept {return y;}

    void setY(float newY) noexcept {y = newY;}

    void jump(const int bonusValue) noexcept {speed = bonusValue + 23;}

    const float getPlayerWidth() const;

    const float getPlayerHeight() const;

    [[nodiscard]] float getSpeed() const noexcept {return speed;}

    void moveHorizontally(float dx) noexcept;

    [[nodiscard]] inline bool playerOnMaxHeight() const noexcept;

    [[nodiscard]] inline float getMaxHeight() const noexcept;
};

class World : public std::enable_shared_from_this<World> {
private:
    bool lastJumpedOn;
    BGTile* lastJumpedOnTile;
    std::list<std::shared_ptr<WorldObserver>> _observers;
    std::unique_ptr<BGTileFactory> tileFactory;
    std::vector<std::unique_ptr<BGTile>> tiles;
    std::unique_ptr<Player> player;
    const float PlatformSizeX;
    const float PlatformSizeY;
    const float maxWidth;
    const float maxHeight;
    float minDifX;
    float maxDifY;
    float minDifY;
    float worldOffSetY;
    unsigned int maxAmountOfTiles;
    struct TileSpawnChances {
        int white;
        int blue;
        int yellow;
        int green;
    };
    TileSpawnChances getSpawnChances(int height) const;
    [[nodiscard]] std::pair<float, float> getFreePosInitialization() const;
    void updateObservers();
    [[nodiscard]]bool isValid(int y) const noexcept;
    void removeTile(const BGTile *targetTile) noexcept;
    [[nodiscard]]float getHighestTileY() const noexcept;
public:
    bool isLastJumpedOn() const;

    // World is eigenaar van de factory
    void addObserver(const std::shared_ptr<WorldObserver>& observer);
    explicit World(std::unique_ptr<BGTileFactory> factory);
    void update(double dt, Direction moveInput);
    void initializeWorld(const std::shared_ptr<World>& self);
    [[nodiscard]] float getWorldOffSetY() const;
    [[nodiscard]] const std::vector<std::unique_ptr<BGTile>> &getTiles() const;
    [[nodiscard]] std::pair<float, float> getPlayerPos()const;
    const float getMaxHeight() const;
    [[nodiscard]] float getMaxPlayerHeight() const noexcept;
};



#endif //ADVACEDPROGRAMINGZIT2_WORLD_H
