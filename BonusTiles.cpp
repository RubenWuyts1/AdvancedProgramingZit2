//
// Created by ruben on 30/07/25.
//

#include "BonusTiles.h"

namespace Tile::Bonus {

    // Constructor voor algemene BonusTile
    // Stelt bonusType in en bepaalt bijhorende waarde (Spring of Jetpack)
    BonusTile::BonusTile(float x, float y, BonusType bonusType) noexcept: BGTile(x, y), bonusType{bonusType},
                                                                          bonusValue{0.0f} {
        if (bonusType == BonusType::Jetpack) {
            bonusValue = 50.0f;
        } else if (bonusType == BonusType::Spring) {
            bonusValue = 15.0f;
        }
    }

    // Groene bonus-tegel (statisch)
    GreenBGTile::GreenBGTile(float x, float y, BonusType bonusType) noexcept: BonusTile(x, y, bonusType) {}

    // Blauwe bonus-tegel (horizontale beweging)
    BlueBGTile::BlueBGTile(float x, float y, BonusType bonusType) noexcept: BonusTile(x, y, bonusType) {}

    // Beweegt horizontaal heen en weer binnen grenzen
    void BlueBGTile::update(int maxWidth, int platformSize) noexcept {
        if (posX > maxWidth - platformSize) {
            movingRight = false;
        } else if (posX <= 1) {
            movingRight = true;
        }
        posX += movingRight ? 4 : -4;
    }

    // Gele bonus-tegel (verticale oscillatie)
    YellowBGTile::YellowBGTile(float x, float y, BonusType bonusType) noexcept: BonusTile(x, y, bonusType) {}

    // Beweegt op en neer tussen een vast aantal frames
    void YellowBGTile::update(int /*maxWidth*/, int /*platformSize*/) noexcept {
        if (moveCounter > 50) {
            movingUp = false;
        } else if (moveCounter < -50) {
            movingUp = true;
        }
        if (movingUp) {
            posY -= 4;
            moveCounter++;
        } else {
            posY += 4;
            moveCounter--;
        }
    }

    // Witte bonus-tegel (verdwijnt na gebruik, gedrag extern geregeld)
    WhiteBGTile::WhiteBGTile(float x, float y, BonusType bonusType) noexcept: BonusTile(x, y, bonusType) {}
}