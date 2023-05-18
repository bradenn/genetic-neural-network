//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENES_SIMULATOR_H
#define GENES_SIMULATOR_H


#include "gfx.h"
#include "genetic/genome.h"
#include "genetic/population.h"

class Simulator {
public:
    Simulator();

    void render();

    void tick();

private:

    GFX *gfx;
    Population *population;
};


#endif //GENES_SIMULATOR_H
