//
// Created by ruben on 23/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_SINGLETONS_H
#define ADVACEDPROGRAMINGZIT2_SINGLETONS_H

#include <chrono>
#include <random>
using Engine = std::default_random_engine;
using floatDistribution = std::uniform_real_distribution<float>;
using intDistribution = std::uniform_int_distribution<int>;

namespace util {
    class Random {
    private:
        static Random* _instance;
        Random() = default;
        Engine engine;
    public:
        Random(const Random&) = delete;
        Random& operator=(const Random&) = delete;
        static Random* getInstance();
        static void destroyInstance();
        [[nodiscard]] int randomValue(int min, int max) noexcept;       // int-versie
        [[nodiscard]] float randomFloat(float min, float max) noexcept; // optioneel behouden
        [[nodiscard]] bool getChance(float probability) noexcept;
    };

    inline int randomValue(int min, int max) {
        return Random::getInstance()->randomValue(min, max);
    }

    inline float randomFloat(float min, float max) {
        return Random::getInstance()->randomFloat(min, max);
    }

    inline float getChance(float probability) {
        return Random::getInstance()->getChance(probability);
    }
}


class Stopwatch {
private:
    using clock = std::chrono::steady_clock;
    clock::time_point lastTick;

    // Singleton instantie
    static Stopwatch* _instance;

    // Privé constructor
    Stopwatch() {
        lastTick = clock::now();
    }

public:
    ~Stopwatch() = default;

    // Verwijder copy
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;

    // Singleton access
    static Stopwatch* getInstance() {
        if (!_instance)
            _instance = new Stopwatch();
        return _instance;
    }

    // Reset timer
    void reset() {
        lastTick = clock::now();
    }

    // Tijd sinds vorige tick (in seconden)
    double tick() {
        auto now = clock::now();
        std::chrono::duration<double> elapsed = now - lastTick;
        lastTick = now;
        return elapsed.count(); // seconden als double
    }
};


#endif //ADVACEDPROGRAMINGZIT2_SINGLETONS_H
