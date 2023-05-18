//
// Created by Braden Nicholson on 5/16/23.
//

#ifndef GENES_POPULATION_H
#define GENES_POPULATION_H


#include "genome.h"

class Population {

public:
    Population(int size);

    void render(GFX *g);

    void tick();

private:

    vector<Genome*> genomes;

    double px = 0;
    double py = 0;

    int round = 0;
    int ticks = 0;

};


#endif //GENES_POPULATION_H
