//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_BGTILE_H
#define ADVACEDPROGRAMINGZIT2_BGTILE_H

#include <string>
#include <memory>
#include "Singletons.h"

enum class Color {Green, Blue, Yellow, White};
enum class BonusType {None, Spring, Jetpack};

class BGTile {
protected:
    float posX;
    float posY;
public:
    BGTile(float x, float y);
    virtual ~BGTile() = default;

    [[nodiscard]] float getPosX() const noexcept {return posX;};
    [[nodiscard]] float getPosY() const noexcept {return posY;};
    [[nodiscard]] std::pair<float, float> getPos() const noexcept;
    void moveY(float dy) noexcept {posY += dy;};

    [[nodiscard]] virtual Color getColor() const = 0;

    // Bonus-gerelateerde interface
    [[nodiscard]] virtual bool hasBonus() const noexcept { return false; }
    [[nodiscard]] virtual BonusType getBonusType() const noexcept { return BonusType::None; }
    [[nodiscard]] virtual float getBonusValue() const noexcept { return 0.0f; }
    virtual void update(int maxWidth, int platformSize) noexcept {};
};

class greenBGTile : public BGTile {
public:
    greenBGTile(float posX, float posY);
    [[nodiscard]] inline Color getColor() const noexcept final {return Color::Green;}
    ~greenBGTile() override = default;
};

class blueBGTile : public BGTile {
private:
    bool movingRight = false;
public:
    void update(int maxWidth, int platformSize) noexcept override;
    blueBGTile(float posX, float posY);
    [[nodiscard]] inline Color getColor() const noexcept final {return Color::Blue;}
    ~blueBGTile() override = default;
};

class yellowBGTile : public BGTile {
private:
    bool movingUp = false;
    int moveCounter = 0;
public:
    void update(int maxWidth, int platformSize) noexcept override;
    yellowBGTile(float posX, float posY);
    [[nodiscard]] inline Color getColor() const noexcept final {return Color::Yellow;}
    ~yellowBGTile() override = default;
};

class whiteBGTile : public BGTile {
public:
    whiteBGTile(float posX, float posY);
    [[nodiscard]] inline Color getColor() const noexcept final {return Color::White;}
    ~whiteBGTile() override = default;
};

class BonusTile : public BGTile {
protected:
    BonusType bonusType;
    float bonusValue;
public:
    BonusTile(float x, float y, BonusType bonusType) : BGTile(x,y), bonusType{bonusType} {
        if (bonusType == BonusType::Jetpack) {
            bonusValue = 75;
        } else if (bonusType == BonusType::Spring) {
            bonusValue = 25;
        } else bonusValue = 0;
    };
    [[nodiscard]] Color getColor() const override = 0;
    [[nodiscard]] bool hasBonus() const noexcept override {return true;};
    [[nodiscard]] BonusType getBonusType() const noexcept override {return bonusType;};
    [[nodiscard]] float getBonusValue() const noexcept override {return bonusValue;};

    ~BonusTile() override = default;
};

class BonusTileGreen : public BonusTile {
public:
    BonusTileGreen(float x, float y, BonusType bonusType) : BonusTile(x, y, bonusType) {}
    [[nodiscard]] Color getColor() const final {return Color::Green;};
    ~BonusTileGreen() override = default;
};

class BonusTileBlue : public BonusTile {
private:
    bool movingRight;
public:
    void update(int maxWidth, int platformSize) noexcept override;
    BonusTileBlue(float x, float y, BonusType bonusType) : BonusTile(x, y, bonusType) {}
    [[nodiscard]] Color getColor() const final {return Color::Blue;};
    ~BonusTileBlue() override = default;
};

class BonusTileYellow : public BonusTile {
private:
    int moveCounter = 0;
    bool movingUp = false;
public:
    void update(int maxWidth, int platformSize) noexcept override;
    BonusTileYellow(float x, float y, BonusType bonusType) : BonusTile(x, y, bonusType) {}
    [[nodiscard]] Color getColor() const final {return Color::Yellow;};
    ~BonusTileYellow() override = default;
};

class BonusTileWhite : public BonusTile {
public:
    BonusTileWhite(float x, float y, BonusType bonusType) : BonusTile(x, y, bonusType) {}
    [[nodiscard]] Color getColor() const final {return Color::White;};
    ~BonusTileWhite() override = default;
};

class BGTileFactory {
public:
    virtual std::unique_ptr<BGTile> createGreen(float posX, float posY) = 0;
    virtual std::unique_ptr<BGTile> createBlue(float posX, float posY) = 0;
    virtual std::unique_ptr<BGTile> createYellow(float posX, float posY) = 0;
    virtual std::unique_ptr<BGTile> createWhite(float posX, float posY) = 0;
    virtual ~BGTileFactory() = default;
};

class DefaultBGTileFactory : public BGTileFactory {
private:
    float chanceSpring = 0.05;
    float chanceJetpack = 0.02;
public:
    std::unique_ptr<BGTile> createGreen(float posX, float posY) override {
        if (util::Random::getInstance()->getChance(chanceSpring)) {
            return std::make_unique<BonusTileGreen>(posX, posY, BonusType::Spring);
        } else if (util::Random::getInstance()->getChance(chanceJetpack)) {
            return std::make_unique<BonusTileGreen>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<greenBGTile>(posX, posY);
    }
    std::unique_ptr<BGTile> createBlue(float posX, float posY) override {
        if (util::Random::getInstance()->getChance(chanceSpring)) {
            return std::make_unique<BonusTileBlue>(posX, posY, BonusType::Spring);
        } else if (util::Random::getInstance()->getChance(chanceJetpack)) {
            return std::make_unique<BonusTileBlue>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<blueBGTile>(posX, posY);
    }
    std::unique_ptr<BGTile> createYellow(float posX, float posY) override {
        if (util::Random::getInstance()->getChance(chanceSpring)) {
            return std::make_unique<BonusTileYellow>(posX, posY, BonusType::Spring);
        } else if (util::Random::getInstance()->getChance(chanceJetpack)) {
            return std::make_unique<BonusTileYellow>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<yellowBGTile>(posX, posY);
    }
    std::unique_ptr<BGTile> createWhite(float posX, float posY) override {
        if (util::Random::getInstance()->getChance(chanceSpring)) {
            return std::make_unique<BonusTileWhite>(posX, posY, BonusType::Spring);
        } else if (util::Random::getInstance()->getChance(chanceJetpack)) {
            return std::make_unique<BonusTileWhite>(posX, posY, BonusType::Jetpack);
        }
        return std::make_unique<whiteBGTile>(posX, posY);
    }
};



#endif //ADVACEDPROGRAMINGZIT2_BGTILE_H
