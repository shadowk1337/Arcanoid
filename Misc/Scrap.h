#pragma once

#include <cstdint>
#include <random>

using Color = uint32_t;

#define CIRCLE_BALL
//#define SQUARE_BALL

#define BALL_CAN_REFLECT_SIDE_EDGE


// https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container
template<typename Iterator, typename RandomGenerator>
Iterator SelectRandom(Iterator start, Iterator end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iterator>
Iterator SelectRandom(Iterator start, Iterator end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return SelectRandom(start, end, gen);
}

float RandomFloat(float min, float max);