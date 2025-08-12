//
// Created by ruben on 30/07/25.
//

#include "BGTileFactory.h"
#include "Random.h"

namespace Tile::Factory {
    std::unique_ptr<BGTile> DefaultBGTileFactory::createGreen(float posX, float posY) {
        auto rng = util::Random::getInstance();
        if (rng->getChance(chanceSpring)) {
            return std::make_unique<Tile::Bonus::GreenBGTile>(posX, posY, BonusType::Spring);
        } else if (rng->getChance(chanceJetpack)) {
            return std::make_unique<Tile::Bonus::GreenBGTile>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<Tile::Normal::GreenBGTile>(posX, posY);
    }

    std::unique_ptr<BGTile> DefaultBGTileFactory::createBlue(float posX, float posY) {
        auto rng = util::Random::getInstance();
        if (rng->getChance(chanceSpring)) {
            return std::make_unique<Tile::Bonus::BlueBGTile>(posX, posY, BonusType::Spring);
        } else if (rng->getChance(chanceJetpack)) {
            return std::make_unique<Tile::Bonus::BlueBGTile>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<Tile::Normal::BlueBGTile>(posX, posY);
    }

    std::unique_ptr<BGTile> DefaultBGTileFactory::createYellow(float posX, float posY) {
        auto rng = util::Random::getInstance();
        if (rng->getChance(chanceSpring)) {
            return std::make_unique<Tile::Bonus::YellowBGTile>(posX, posY, BonusType::Spring);
        } else if (rng->getChance(chanceJetpack)) {
            return std::make_unique<Tile::Bonus::YellowBGTile>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<Tile::Normal::YellowBGTile>(posX, posY);
    }

    std::unique_ptr<BGTile> DefaultBGTileFactory::createWhite(float posX, float posY) {
        auto rng = util::Random::getInstance();
        if (rng->getChance(chanceSpring)) {
            return std::make_unique<Tile::Bonus::WhiteBGTile>(posX, posY, BonusType::Spring);
        } else if (rng->getChance(chanceJetpack)) {
            return std::make_unique<Tile::Bonus::WhiteBGTile>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<Tile::Normal::WhiteBGTile>(posX, posY);
    }
}