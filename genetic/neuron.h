//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENETIC_ROBOT_NEURON_H
#define GENETIC_ROBOT_NEURON_H

#include <cstdint>
#include "source.h"

class Neuron : public Source {

public:
    Neuron(uint16_t type, uint16_t id, uint16_t value) : Source(type, id, value) {

    }


};


#endif //GENETIC_ROBOT_NEURON_H
