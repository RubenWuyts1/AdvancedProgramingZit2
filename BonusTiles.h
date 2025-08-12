//
// Created by ruben on 30/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_BONUSTILES_H
#define ADVACEDPROGRAMINGZIT2_BONUSTILES_H

#include "BGTile.h"

namespace Tile::Bonus {
    /**
     * @brief Abstract base class for tiles with bonuses.
     */
    class BonusTile : public BGTile {
    protected:
        BonusType bonusType;
        float bonusValue;
    public:
        /**
         * @brief Constructs a bonus tile with given type and position.
         */
        BonusTile(float x, float y, BonusType bonusType) noexcept;

        [[nodiscard]] inline bool hasBonus() const noexcept final { return true; };

        [[nodiscard]] inline BonusType getBonusType() const noexcept final { return bonusType; };

        [[nodiscard]] inline float getBonusValue() const noexcept final { return bonusValue; };

        /// Color must be defined by derived class
        [[nodiscard]] Color getColor() const noexcept override = 0;

        ~BonusTile() override = default;
    };

    /**
     * @brief Static green bonus tile.
     */
    class GreenBGTile final : public BonusTile {
    public:
        GreenBGTile(float x, float y, BonusType bonusType) noexcept;

        [[nodiscard]] inline Color getColor() const noexcept final { return Color::Green; };

        ~GreenBGTile() override = default;
    };

    /**
     * @brief Horizontally moving blue bonus tile.
     */
    class BlueBGTile final : public BonusTile {
    private:
        bool movingRight = false;
    public:
        BlueBGTile(float x, float y, BonusType bonusType) noexcept;

        void update(int maxWidth, int platformSize) noexcept override;

        [[nodiscard]] inline Color getColor() const noexcept final { return Color::Blue; };

        ~BlueBGTile() override = default;
    };

    /**
     * @brief Vertically oscillating yellow bonus tile.
     */
    class YellowBGTile final : public BonusTile {
    private:
        int moveCounter = 0;
        bool movingUp = false;
    public:
        YellowBGTile(float x, float y, BonusType bonusType) noexcept;

        void update(int maxWidth, int platformSize) noexcept override;

        [[nodiscard]] inline Color getColor() const noexcept final { return Color::Yellow; };

        ~YellowBGTile() override = default;
    };

    /**
     * @brief Temporary white bonus tile.
     */
    class WhiteBGTile final : public BonusTile {
    public:
        WhiteBGTile(float x, float y, BonusType bonusType) noexcept;

        [[nodiscard]] inline Color getColor() const noexcept final { return Color::White; };

        ~WhiteBGTile() override = default;
    };
}

#endif //ADVACEDPROGRAMINGZIT2_BONUSTILES_H