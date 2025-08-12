//
// Created by ruben on 30/07/25.
//

#include "Stopwatch.h"

namespace util {

    // Initialize the singleton instance pointer to nullptr
    Stopwatch* Stopwatch::_instance = nullptr;

    // Constructor sets the initial tick time
    Stopwatch::Stopwatch() {
        lastTick = clock::now();
    }

    // Returns the singleton instance of Stopwatch (lazily constructed)
    Stopwatch* Stopwatch::getInstance() {
        if (!_instance)
            _instance = new Stopwatch();
        return _instance;
    }

    // Resets the internal timer to the current time
    void Stopwatch::reset() {
        lastTick = clock::now();
    }

    // Returns the time in seconds since the last tick and updates lastTick
    double Stopwatch::tick() {
        auto now = clock::now();
        std::chrono::duration<double> elapsed = now - lastTick;
        lastTick = now;
        return elapsed.count();
    }

}