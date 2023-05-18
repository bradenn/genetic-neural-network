//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENETIC_ROBOT_STIMULUS_H
#define GENETIC_ROBOT_STIMULUS_H

#include <cstdint>
#include "source.h"

class Stimulus : public Source {

public:
    Stimulus(uint16_t type, uint16_t id, uint16_t value) : Source(type, id, value) {

    }


};


#endif //GENETIC_ROBOT_STIMULUS_H
