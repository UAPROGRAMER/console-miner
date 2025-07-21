#include <functions.hpp>

#include <chrono>
#include <thread>

void sleep(unsigned long ms) {
    if (ms != 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}