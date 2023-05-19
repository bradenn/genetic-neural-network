//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENES_SIMULATOR_H
#define GENES_SIMULATOR_H


#include "gfx.h"
#include "genetic/genome.h"
#include "genetic/population.h"
#include "window/frame.h"
#include "genetic/world.h"
#include "genetic/statistics.h"

class Simulator {
public:
    Simulator();

    void render();


private:

    Frame *frame;

    GFX *gfx;
    World *world;
    Statistics *statistics;
    Population *population;
};


#endif //GENES_SIMULATOR_H
