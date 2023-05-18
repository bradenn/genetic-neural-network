//
// Created by Braden Nicholson on 5/13/23.
//

#ifndef GENETIC_ROBOT_GENE_H
#define GENETIC_ROBOT_GENE_H


#include <cstdint>
#include <cstdlib>
#include <random>
#include <array>

// inspired by https://github.com/davidrmiller/biosim4/blob/main/src/genome-neurons.h

const uint8_t INPUT = 1;
const uint8_t NEURON = 0;
const uint8_t OUTPUT = 1;

struct Gene {
    uint16_t sourceType:1;
    uint16_t sourceId:7;

    uint16_t destinationType:1;
    uint16_t destinationId:7;

    uint16_t weight;

    float normalizeWeight() const {
        return (float) weight / 65536.0f;
    }

    static int16_t randomWeight() {
        return rand() % 65536;
    }
};

static void flipRandomBit(Gene& gene) {
    std::random_device rd;
    std::mt19937 generator(rd());

    // The size of the struct in bytes (should be 4 for your struct)
    const size_t sizeInBytes = sizeof(Gene);

    // Convert the struct to an array of bytes
    std::array<uint8_t, sizeInBytes> bytes;
    std::memcpy(bytes.data(), &gene, sizeInBytes);

    // Uniform distributions for byte and bit selection
    std::uniform_int_distribution<size_t> byteDistribution(0, sizeInBytes - 1);
    std::uniform_int_distribution<int> bitDistribution(0, 7);

    // Select a random byte and a random bit within that byte
    size_t randomByte = byteDistribution(generator);
    int randomBit = bitDistribution(generator);

    // Flip the selected bit
    bytes[randomByte] ^= 1 << randomBit;

    // Copy the modified bytes back into the struct
    std::memcpy(&gene, bytes.data(), sizeInBytes);
}
#endif //GENETIC_ROBOT_GENE_H
