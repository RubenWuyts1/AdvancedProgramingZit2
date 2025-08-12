//
// Created by ruben on 30/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_BGTILEFACTORY_H
#define ADVACEDPROGRAMINGZIT2_BGTILEFACTORY_H

#include <memory>
#include "NormalTiles.h"
#include "BonusTiles.h"

namespace Tile::Factory {
    /**
     * @brief Abstract factory interface for creating BGTile objects.
     */
    class BGTileFactory {
    public:
        virtual std::unique_ptr<BGTile> createGreen(float posX, float posY) = 0;

        virtual std::unique_ptr<BGTile> createBlue(float posX, float posY) = 0;

        virtual std::unique_ptr<BGTile> createYellow(float posX, float posY) = 0;

        virtual std::unique_ptr<BGTile> createWhite(float posX, float posY) = 0;

        virtual ~BGTileFactory() = default;
    };

    /**
     * @brief Default implementation that randomly adds bonuses to tiles.
     */
    class DefaultBGTileFactory final : public BGTileFactory {
    private:
        float chanceSpring = 0.05f;
        float chanceJetpack = 0.02f;
    public:
        std::unique_ptr<BGTile> createGreen(float posX, float posY) override;

        std::unique_ptr<BGTile> createBlue(float posX, float posY) override;

        std::unique_ptr<BGTile> createYellow(float posX, float posY) override;

        std::unique_ptr<BGTile> createWhite(float posX, float posY) override;
    };
}


#endif //ADVACEDPROGRAMINGZIT2_BGTILEFACTORY_H
