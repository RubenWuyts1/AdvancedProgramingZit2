//
// Created by ruben on 30/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_RANDOM_H
#define ADVACEDPROGRAMINGZIT2_RANDOM_H


#include <random>

using Engine = std::default_random_engine;
using FloatDistribution = std::uniform_real_distribution<float>;
using IntDistribution = std::uniform_int_distribution<int>;

#include <random>

using Engine = std::default_random_engine;
using FloatDistribution = std::uniform_real_distribution<float>;
using IntDistribution = std::uniform_int_distribution<int>;

namespace util {
    /**
     * @class Random
     * @brief Singleton random number generator with manual instance control.
     */
    class Random {
    private:
        Random();  // private constructor
        ~Random() = default;

        static Random *_instance;
        Engine engine;
    public:
        Random(const Random &) = delete;

        Random &operator=(const Random &) = delete;

        /**
         * @brief Access the global Random instance.
         * @return Pointer to the Random singleton.
         */
        static Random *getInstance();

        /**
         * @brief Returns a random integer in the range [min, max].
         */
        [[nodiscard]] int randomValue(int min, int max) noexcept;

        /**
         * @brief Returns a random float in the range [min, max].
         */
        [[nodiscard]] float randomFloat(float min, float max) noexcept;

        /**
         * @brief Returns true with the given probability (between 0.0 and 1.0).
         */
        [[nodiscard]] bool getChance(float probability) noexcept;
    };

    // Convenience inline helpers
    inline int randomValue(int min, int max) {
        return Random::getInstance()->randomValue(min, max);
    }

    inline float randomFloat(float min, float max) {
        return Random::getInstance()->randomFloat(min, max);
    }

    inline bool getChance(float probability) {
        return Random::getInstance()->getChance(probability);
    }
}

#endif //ADVACEDPROGRAMINGZIT2_RANDOM_H
