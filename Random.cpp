//
// Created by ruben on 30/07/25.
//

#include "Random.h"

namespace util {
    // Initialize static pointer to null
    Random *Random::_instance = nullptr;

    // Private constructor: seed the random engine using std::random_device
    Random::Random() {
        std::random_device rd;
        engine.seed(rd());
    }

    // Accessor for the singleton instance (manual memory management)
    Random *Random::getInstance() {
        if (!_instance)
            _instance = new Random();
        return _instance;
    }

    // Return a random integer between min and max
    int Random::randomValue(int min, int max) noexcept {
        IntDistribution dist(min, max);
        return dist(engine);
    }

    // Return a random float between min and max
    float Random::randomFloat(float min, float max) noexcept {
        FloatDistribution dist(min, max);
        return dist(engine);
    }

    // Return true with the given probability (0.0 to 1.0)
    bool Random::getChance(float probability) noexcept {
        FloatDistribution dist(0.0f, 1.0f);
        return dist(engine) < probability;
    }
}