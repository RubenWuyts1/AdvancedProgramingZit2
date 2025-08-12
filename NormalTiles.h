//
// Created by ruben on 30/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_NORMALTILES_H
#define ADVACEDPROGRAMINGZIT2_NORMALTILES_H

#include "BGTile.h"


namespace Tile::Normal {
    /**
     * @brief Static green background tile.
     * Does not move or disappear.
    */
    class GreenBGTile final : public BGTile {
    public:
        /**
         * @brief Constructs a green tile at the given position.
         * @param posX X-coordinate.
         * @param posY Y-coordinate.
         */
        GreenBGTile(float posX, float posY) noexcept;

        /// @return Color::Green
        [[nodiscard]] inline Color getColor() const noexcept final { return Color::Green; }

        /// Virtual destructor
        ~GreenBGTile() override = default;
    };

    /**
     * @brief Horizontally moving blue tile.
     */
    class BlueBGTile final : public BGTile {
    private:
        bool movingRight = false;
    public:
        /**
         * @brief Constructs a blue tile at the given position.
         * @param posX X-coordinate.
         * @param posY Y-coordinate.
         */
        BlueBGTile(float posX, float posY) noexcept;

        /**
         * @brief Moves tile left/right within bounds.
         * @param maxWidth Maximum horizontal screen size.
         * @param platformSize Size of the tile.
         */
        void update(int maxWidth, int platformSize) noexcept override;

        /// @return Color::Blue
        [[nodiscard]] inline Color getColor() const noexcept final { return Color::Blue; }

        /// Virtual destructor
        ~BlueBGTile() override = default;
    };

    /**
     * @brief Vertically oscillating yellow tile.
     */
    class YellowBGTile final : public BGTile {
    private:
        bool movingUp = false;
        int moveCounter = 0;
    public:
        /**
         * @brief Constructs a yellow tile at the given position.
         * @param posX X-coordinate.
         * @param posY Y-coordinate.
         */
        YellowBGTile(float posX, float posY) noexcept;

        /**
         * @brief Moves tile up and down within a range.
         * @param maxWidth Ignored (horizontal movement unused).
         * @param platformSize Controls movement range.
         */
        void update(int maxWidth, int platformSize) noexcept override;

        /// @return Color::Yellow
        [[nodiscard]] inline Color getColor() const noexcept final { return Color::Yellow; }

        /// Virtual destructor
        ~YellowBGTile() override = default;
    };

    /**
     * @brief Temporary white tile that disappears after use.
     */
    class WhiteBGTile final : public BGTile {
    public:
        /**
         * @brief Constructs a white tile at the given position.
         * @param posX X-coordinate.
         * @param posY Y-coordinate.
         */
        WhiteBGTile(float posX, float posY) noexcept;

        /// @return Color::White
        [[nodiscard]] inline Color getColor() const noexcept final { return Color::White; }

        /// Virtual destructor
        ~WhiteBGTile() override = default;
    };
}


#endif //ADVACEDPROGRAMINGZIT2_NORMALTILES_H
