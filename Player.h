//
// Created by ruben on 30/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_PLAYER_H
#define ADVACEDPROGRAMINGZIT2_PLAYER_H


#include <utility>

/**
 * @brief Represents the player character in the game world.
 */
class Player {
private:
    float x;
    float y;
    float maxY;
    float speed;

    const float playerWidth;
    const float playerHeight;
    const float worldWidth;

    static constexpr float gravity = 25.0f;
    static constexpr float jumpBase = 18.0f;
public:
    /**
     * @brief Constructs the player at given position and size.
     */
    Player(float x, float y, float playerWidth, float playerHeight, float worldWidth) noexcept;

    /**
     * @brief Moves the player vertically based on delta time and gravity.
     */
    void moveVertically(double dt, float &worldOffsetY) noexcept;

    /**
     * @brief Moves the player horizontally.
     */
    void moveHorizontally(float dx) noexcept;

    /// @brief Makes the player jump with optional bonus power.
    inline void jump(int bonusValue) noexcept { speed = static_cast<float>(bonusValue) + jumpBase; }

    /// @return Current X position
    [[nodiscard]] inline float getX() const noexcept { return x; }

    /// @return Current Y position
    [[nodiscard]] inline float getY() const noexcept { return y; }

    /// Sets the Y position of the player
    inline void setY(float newY) noexcept { y = newY; }

    /// @return Player width
    [[nodiscard]] inline float getPlayerWidth() const noexcept { return playerWidth; }

    /// @return Player height
    [[nodiscard]] inline float getPlayerHeight() const noexcept { return playerHeight; }

    /// @return Current vertical speed
    [[nodiscard]] inline float getSpeed() const noexcept { return speed; }

    /// @return Whether the player is at their highest Y position
    [[nodiscard]] inline bool playerOnMaxHeight() const noexcept { return y == maxY; }

    /// @return The highest Y position reached so far
    [[nodiscard]] inline float getMaxHeight() const noexcept { return maxY; }
};

#endif //ADVACEDPROGRAMINGZIT2_PLAYER_H
