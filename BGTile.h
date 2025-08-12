//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_BGTILE_H
#define ADVACEDPROGRAMINGZIT2_BGTILE_H

#include <utility>

namespace Tile {
    enum class Color {
        Green, Blue, Yellow, White
    };
    enum class BonusType {
        None, Spring, Jetpack
    };

    /**
 * @brief Abstract base class for background tiles.
 */
    class BGTile {
    protected:
        float posX;
        float posY;
    public:
        /// Construct tile at (x, y)
        constexpr BGTile(float x, float y) noexcept: posX{x}, posY{y} {}

        /// Virtual destructor
        virtual ~BGTile() = default;

        /// @return X-position
        [[nodiscard]] inline float getPosX() const noexcept { return posX; }

        /// @return Y-position
        [[nodiscard]] inline float getPosY() const noexcept { return posY; }

        /// @return (X, Y) position
        [[nodiscard]] inline std::pair<float, float> getPos() const noexcept { return {posX, posY}; }

        /// Move tile vertically
        inline void moveY(float dy) noexcept { posY += dy; }

        /// @return Tile color (pure virtual)
        [[nodiscard]] virtual inline Color getColor() const noexcept = 0;

        /// @return Whether tile has a bonus
        [[nodiscard]] virtual bool hasBonus() const noexcept { return false; }

        /// @return Bonus type
        [[nodiscard]] virtual inline BonusType getBonusType() const noexcept { return BonusType::None; }

        /// @return Bonus value
        [[nodiscard]] virtual inline float getBonusValue() const noexcept { return 0.0f; }

        /// Update tile state
        virtual void update(int /*maxWidth*/, int /*platformSize*/) noexcept {}
    };
}

#endif //ADVACEDPROGRAMINGZIT2_BGTILE_H