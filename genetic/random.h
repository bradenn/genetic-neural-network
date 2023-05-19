//
// Created by Braden Nicholson on 5/17/23.
//

#ifndef GENES_RANDOM_H
#define GENES_RANDOM_H

#include <cstdint>
#include <random>

static int randomUInt() {
    auto a = std::chrono::steady_clock::now();
    auto value = (a.time_since_epoch().count())/1000;
    std::srand(value);
    return std::rand();
}
static uint16_t randomU16Bit() {

    // Random number engine
    std::random_device rd;
    std::default_random_engine generator(rd());

    // Uniform distribution over the range [0, 15]
    std::uniform_int_distribution<int> distribution(0, 15);

    // Generate a random bit position
    int bitPosition = distribution(generator);

    // Return a uint16_t with that bit set to one and the rest set to zero
    return static_cast<uint16_t>(1 << bitPosition);

}

#endif //GENES_RANDOM_H
