//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENETIC_ROBOT_SOURCE_H
#define GENETIC_ROBOT_SOURCE_H

#include <cstdint>

class Source {

public:
    Source(uint16_t type, uint16_t id, uint16_t value);
protected:
    uint16_t type: 1;
    uint16_t id: 7;
    uint16_t value;

};


#endif //GENETIC_ROBOT_SOURCE_H
