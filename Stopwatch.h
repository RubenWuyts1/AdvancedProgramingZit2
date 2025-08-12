//
// Created by ruben on 30/07/25.
//

#ifndef ADVACEDPROGRAMINGZIT2_STOPWATCH_H
#define ADVACEDPROGRAMINGZIT2_STOPWATCH_H

#include <chrono>

namespace util {
    /**
     * @class Stopwatch
     * @brief Singleton class that measures time intervals between game updates.
     *
     * Ensures consistent timing across different devices by dynamically measuring frame intervals.
     * Designed using the Singleton pattern.
     */
    class Stopwatch {
    private:
        Stopwatch();  // Constructor is private for Singleton
        ~Stopwatch() = default;
        using clock = std::chrono::steady_clock;
        clock::time_point lastTick;
        static Stopwatch *_instance;
    public:
        Stopwatch(const Stopwatch &) = delete;
        Stopwatch &operator=(const Stopwatch &) = delete;
        /**
         * @brief Access the singleton Stopwatch instance.
         * @return Pointer to the single Stopwatch instance.
         */
        static Stopwatch *getInstance();
        /**
         * @brief Resets the stopwatch to the current time.
         */
        void reset();
        /**
         * @brief Returns the time elapsed since the last tick.
         * @return Time in seconds as double.
         */
        [[nodiscard]] double tick();
    };
}


#endif //ADVACEDPROGRAMINGZIT2_STOPWATCH_H
