//
// Created by ruben on 23/07/25.
//

#include "Singletons.h"
using util::Random;

Stopwatch* Stopwatch::_instance = nullptr;

Random* util::Random::_instance = nullptr;

Random* Random::getInstance() {
    if (!_instance) {
        _instance = new Random();
        std::random_device rd;
        _instance->engine.seed(rd());
    }
    return _instance;
}

void Random::destroyInstance() {
    delete _instance;
    _instance = nullptr;
}

int Random::randomValue(int min, int max) noexcept {
    intDistribution dist(min, max);
    return dist(engine);
}

float Random::randomFloat(float min, float max) noexcept {
    floatDistribution dist(min, max);
    return dist(engine);
}

bool Random::getChance(float probability) noexcept {
    if (probability > 1) return false;
    probability = std::clamp(probability, 0.0f, 1.0f);
    floatDistribution dist(0.0f, 1.0f);
    return dist(engine) < probability;
}

