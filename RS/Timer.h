//
// Created by AC on 2023/5/15.
//

#pragma once

#include <iostream>
#include <chrono>

class Timer {
public:
    static Timer *getInstance() {
        if (timer == nullptr) {
            timer = new Timer();
        }
        return timer;
    }

    void start_time() {
        last_time = std::chrono::steady_clock::now();
    }

    void get_elapsed() {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(now - last_time);
        std::cout << "duration:" << duration << std::endl;
    }

private:
    Timer() : last_time(std::chrono::steady_clock::now()) {};
    std::chrono::time_point<std::chrono::steady_clock> last_time;
    inline static Timer *timer = nullptr;
};

#define START_TIMER Timer::getInstance()->start_time();
#define STOP_TIMER Timer::getInstance()->get_elapsed();

