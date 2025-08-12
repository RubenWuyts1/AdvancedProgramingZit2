//
// Created by ruben on 30/07/25.
//

#include "NormalTiles.h"

namespace Tile::Normal {
    // Constructor voor groene statische tegel
    GreenBGTile::GreenBGTile(float posX, float posY) noexcept: BGTile(posX, posY) {}

    // Constructor voor blauwe bewegende tegel
    BlueBGTile::BlueBGTile(float posX, float posY) noexcept: BGTile(posX, posY) {}

    void BlueBGTile::update(int maxWidth, int platformSize) noexcept {
        // Keer om bij bereiken van rand
        if (posX > maxWidth - platformSize) {
            movingRight = false;
        }
        if (posX <= 1) {
            movingRight = true;
        }
        // Verplaats horizontaal
        if (movingRight) {
            posX += 4;
        } else {
            posX -= 4;
        }
    }

    // Constructor voor gele verticale tegel
    YellowBGTile::YellowBGTile(float posX, float posY) noexcept: BGTile(posX, posY) {}

    void YellowBGTile::update(int /*maxWidth*/, int /*platformSize*/) noexcept {
        // Wissel richting na een bereik van 50 stappen
        if (moveCounter > 50) {
            movingUp = false;
        }
        if (moveCounter < -50) {
            movingUp = true;
        }
        // Verplaats verticaal en update teller
        if (movingUp) {
            posY -= 4;
            moveCounter++;
        } else {
            posY += 4;
            moveCounter--;
        }
    }

    // Constructor voor witte tijdelijke tegel
    WhiteBGTile::WhiteBGTile(float posX, float posY) noexcept: BGTile(posX, posY) {}
}
