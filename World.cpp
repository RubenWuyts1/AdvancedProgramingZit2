//
// Created by ruben on 23/07/25.
//

#include <iostream>
#include "World.h"

using util::randomValue;

World::World(std::unique_ptr<BGTileFactory> factory) : tileFactory(std::move(factory)), PlatformSizeX(68),
lastJumpedOn(false), lastJumpedOnTile(nullptr),PlatformSizeY(14), maxHeight(700.f), maxWidth(500.f), worldOffSetY(0),
minDifX(75), minDifY(25), maxDifY(225), maxAmountOfTiles(15) {
}

void World::update(double dt, Direction moveInput) {
    float movementX = 0;
    if (moveInput == Direction::Right) {
        movementX = 300;
    } else if (moveInput == Direction::Left) {
        movementX = -300;
    }
    float dx = movementX * static_cast<float>(dt);
    player->moveHorizontally(dx);
    for (auto& tile : tiles) {
        tile->update(maxWidth, PlatformSizeX);
    }
    player->moveVertically(dt, worldOffSetY);
    float playerY = player->getY();
    if (player->playerOnMaxHeight()) {
        worldOffSetY -= maxHeight/1.25;
        for (size_t i = 0; i < tiles.size(); ) {
            if (tiles[i]->getPosY() < worldOffSetY) {
                tiles.erase(tiles.begin() + i);
            } else {
                ++i;
            }
        }
    }
    // Het maken van nieuwe tiles.
    int maxPlayerHeight = static_cast<int>(player->getMaxHeight());
    maxAmountOfTiles = std::max(5, 15 - (maxPlayerHeight / 10000));
    if (tiles.size() < maxAmountOfTiles || maxDifY < worldOffSetY+maxHeight-getHighestTileY()) {
        auto chances = getSpawnChances(maxPlayerHeight);
        int roll = util::randomValue(1, 100); // random int van 1 t/m 100
        int posX = util::randomFloat(0,maxWidth-PlatformSizeX);
        if (roll <= chances.white) {
            tiles.emplace_back(tileFactory->createWhite(posX, worldOffSetY+maxHeight));
        } else if (roll <= chances.white + chances.blue) {
            tiles.emplace_back(tileFactory->createBlue(posX, worldOffSetY+maxHeight));
        } else if (roll <= chances.white + chances.blue + chances.yellow) {
            tiles.emplace_back(tileFactory->createYellow(posX, worldOffSetY+maxHeight));
        } else {
            tiles.emplace_back(tileFactory->createGreen(posX, worldOffSetY+maxHeight));
        }
    }

    // Het jump mechanisme.
    float playerX = player->getX();
    float playerSpeed = player->getSpeed();
    playerY = player->getY();
    lastJumpedOn = false;
    for (const auto& tile : tiles) {
        float tileX = tile->getPosX();
        bool falling = playerSpeed < 0;
        bool withinX = (playerX + player->getPlayerWidth() > tileX) && (playerX < tileX + PlatformSizeX);
        bool passedThrough = tile->getPosY()+5 > playerY && tile->getPosY()-PlatformSizeY-10 < playerY;
        if (passedThrough && falling && withinX) {
            if (lastJumpedOnTile != nullptr && lastJumpedOnTile == tile.get()) {
                lastJumpedOn = true;
            }
            player->jump(tile->getBonusValue());
            if (tile->getColor() == Color::White) {
                removeTile(tile.get());
                lastJumpedOnTile = nullptr;
            } else {
                lastJumpedOnTile = tile.get();
            }
            break;
        }
    }
    //std::cout << lastJumpedOn << std::endl;
    updateObservers();
}

void World::initializeWorld(const std::shared_ptr<World>& self) {
    player = std::make_unique<Player>(maxWidth/2.4, 50,50,80,500);
    tiles.emplace_back(tileFactory->createGreen(maxWidth/2.4, 25));
    for (int i=0; i<maxAmountOfTiles; i++) {
        std::pair<float, float> pos = getFreePosInitialization();
        tiles.emplace_back(tileFactory->createGreen(pos.first,pos.second));
    }
    updateObservers();
}
std::pair<float, float> World::getFreePosInitialization() const {
    using util::randomValue;
    int posX = randomValue(0, std::floor(maxWidth)-PlatformSizeX);
    int posY = randomValue(0, std::floor(maxHeight));
    while (!isValid(posY)) {
        posY = randomValue(0, std::floor(maxHeight));
    }
    return {posX, posY};
}
bool World::isValid(int y) const noexcept {
    bool maxDif = false;
    for (const auto& tile : tiles) {
        if (std::abs(y-tile->getPosY()) < minDifY) {
            return false;
        }
        if (std::abs(y-tile->getPosY() < maxDifY)) {
            maxDif = true;
        }
    }
    return maxDif;
}

float World::getWorldOffSetY() const {
    return worldOffSetY;
}

const std::vector<std::unique_ptr<BGTile>> &World::getTiles() const {
    return tiles;
}

std::pair<float, float> World::getPlayerPos() const {
    return {player->getX(), player->getY()};
}

float World::getHighestTileY() const noexcept {
    float highest = 0.0f;
    for (const auto& tile : tiles) {
        highest = std::max(highest, tile->getPosY());
    }
    return highest;
}

void World::updateObservers() {
    auto self = shared_from_this(); // geeft std::shared_ptr<World>
    for (const auto& observer : _observers) {
        observer->update(self); // wordt impliciet geconverteerd naar weak_ptr
    }
}

void World::addObserver(const std::shared_ptr<WorldObserver>& observer) {
    _observers.push_back(observer);
}

void World::removeTile(const BGTile* targetTile) noexcept {
    auto it = std::remove_if(tiles.begin(), tiles.end(),
                    [targetTile](const std::unique_ptr<BGTile>& tile) {
                         return tile.get() == targetTile;});
    if (it != tiles.end()) {
        tiles.erase(it, tiles.end());
    }
}

const float World::getMaxHeight() const {
    return maxHeight;
}

bool World::isLastJumpedOn() const {
    return lastJumpedOn;
}

float World::getMaxPlayerHeight() const noexcept {
    return player->getMaxHeight();
}

World::TileSpawnChances World::getSpawnChances(int height) const {
    int white = std::min(25, 10 + (height / 10000) * 5);
    int blue = std::min(35, 10 + (height / 10000) * 5);
    int yellow = std::min(20, 5 + (height / 15000) * 5);

    int total = white + blue + yellow;
    int green = std::max(0, 100 - total); // rest

    return {white, blue, yellow, green};
}

Player::Player(float x, float y, const float playerWidth, const float playerHeight, const float worldWidth)
        : x(x), y(y), speed(0), playerWidth(playerWidth), playerHeight(playerHeight), worldWidth(worldWidth) {}

void Player::moveHorizontally(float dx) noexcept {
    x += dx;
    if (x > worldWidth) {
        x = 0;
    }
    if (x < -worldWidth) {
        x = worldWidth-1; // Wrap around to the right
    }
}

void Player::moveVertically(double dt, float& worldOffSet) noexcept {
    speed -= dt*25;
    y += speed;
    if (y > maxY) {
        maxY = y;
        worldOffSet = maxY;
    }
}

const float Player::getPlayerWidth() const {
    return playerWidth;
}

const float Player::getPlayerHeight() const {
    return playerHeight;
}

bool Player::playerOnMaxHeight() const noexcept {
    return y == maxY;
}

float Player::getMaxHeight() const noexcept {
    return maxY;
}


