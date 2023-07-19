#include "Scrap.h"
#include <random>

float RandomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return static_cast<float>(dist(gen));
}