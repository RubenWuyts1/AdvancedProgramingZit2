//
// Created by ruben on 30/07/25.
//

#include "Player.h"

// if maxY(y) the scroll logic isn't correct.
Player::Player(float x, float y, float playerWidth, float playerHeight, float worldWidth) noexcept
        : x(x), y(y), maxY(0), speed(0.0f), playerWidth(playerWidth), playerHeight(playerHeight),
          worldWidth(worldWidth) {}

void Player::moveVertically(double dt, float &worldOffsetY) noexcept {
    speed -= static_cast<float>(dt) * gravity;
    y += speed;
    if (y > maxY) {
        maxY = y;
        worldOffsetY = maxY;
    }
}

void Player::moveHorizontally(float dx) noexcept {
    x += dx;
    if (x > worldWidth) {
        x = 0.0f;
    }
    if (x < -worldWidth) {
        x = worldWidth - 1.0f;
    }
}