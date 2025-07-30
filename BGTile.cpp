//
// Created by ruben on 23/07/25.
//

#include "BGTile.h"

std::pair<float, float> BGTile::getPos() const noexcept {
    return std::pair<float, float>{posX, posY};
}


BGTile::BGTile(float posX, float posY) : posX(posX), posY(posY) {}

greenBGTile::greenBGTile(float posX, float posY) : BGTile(posX, posY) {}

blueBGTile::blueBGTile(float posX, float posY) : BGTile(posX, posY) {}

void blueBGTile::update(int maxWidth, int platformSize) noexcept {
    if (posX > maxWidth -platformSize) {
        movingRight = false;
    }
    if (posX <= 1) {
        movingRight = true;
    }
    if (movingRight) {
        posX += 4;
    } else {
        posX -= 4;
    }
}

yellowBGTile::yellowBGTile(float posX, float posY) : BGTile(posX, posY) {}

void yellowBGTile::update(int maxWidth, int platformSize) noexcept {
    if (moveCounter > 50) {
        movingUp = false;
    }
    if (moveCounter < -50) {
        movingUp = true;
    }
    if (movingUp) {
        posY -= 4;
        moveCounter++;
    } else {
        moveCounter--;
        posY += 4;
    }
}

whiteBGTile::whiteBGTile(float posX, float posY) : BGTile(posX, posY) {}

void BonusTileBlue::update(int maxWidth, int platformSize) noexcept {
    if (posX > maxWidth -platformSize) {
        movingRight = false;
    }
    if (posX <= 1) {
        movingRight = true;
    }
    if (movingRight) {
        posX += 4;
    } else {
        posX -= 4;
    }
}

void BonusTileYellow::update(int maxWidth, int platformSize) noexcept {
    if (moveCounter > 50) {
        movingUp = false;
    }
    if (moveCounter < -50) {
        movingUp = true;
    }
    if (movingUp) {
        posY -= 4;
        moveCounter++;
    } else {
        moveCounter--;
        posY += 4;
    }
}
